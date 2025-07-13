#include "ProjectileManager.h"
#include "IEnemyManager.h"
#include "Projectile.h"
#include "IPlayer.h"
#include <algorithm>
#include <ranges>
#include <iostream>
#include "Enemy.h"

ProjectileManager::ProjectileManager(){}

void ProjectileManager::clear() {
    enemy_projectiles_.clear();
    player_projectiles_.clear();
}

void ProjectileManager::cleanupProjectiles() {
    if (--cleanup_counter_ <= 0) {
        auto is_disabled = [](const std::unique_ptr<Projectile>&obj_ptr) {
            return (obj_ptr->isDisabled());
        };
        cleanup_counter_ = 120;
        auto it_enemy = std::remove_if(enemy_projectiles_.begin(), enemy_projectiles_.end(), is_disabled);
        enemy_projectiles_.erase(it_enemy, enemy_projectiles_.end());
        auto it_player = std::remove_if(player_projectiles_.begin(), player_projectiles_.end(), is_disabled);
        player_projectiles_.erase(it_player, player_projectiles_.end());
    }
}

void ProjectileManager::process(IEnemyManager& enemy_manager, IPlayer& player, IPickupManager& pickup_manager) {
    cleanupProjectiles();

    auto is_not_disabled_generic = []<typename T>(const std::unique_ptr<T>&obj_ptr) {
        return !(obj_ptr->isDisabled());
    };

    for (auto& enemy_projectile : enemy_projectiles_
        | std::views::filter(is_not_disabled_generic)) {
        enemy_projectile->process();
    }
    for (auto& player_projectile : player_projectiles_
        | std::views::filter(is_not_disabled_generic)) {
        player_projectile->process();
    }
    // check collision of enemies with player projectiles
    // break if enemy is disabled after collision
    for (auto& enemy : enemy_manager.getEnemies()
        | std::views::filter(is_not_disabled_generic)) {
        for (auto& projectile : player_projectiles_ | std::views::filter(is_not_disabled_generic)) {
            if (enemy->hitbox_.checkCollision(projectile->getHitbox())) {
                projectile->disable();
                enemy->hit(*projectile, pickup_manager);
                if (enemy->isDisabled())
                    break;
            }
        }
    }
    // check collision of player with enemy projectiles
    // break on the first collision since the player has i_frames
    if (!player.isInvincible()) {
        for (auto& projectile : enemy_projectiles_
            | std::views::filter(is_not_disabled_generic)) {
            if (player.getHitbox().checkCollision(projectile->getHitbox())) {
                player.hit(*projectile);
                projectile->disable();
                break;
            }
        }
    }
}

void ProjectileManager::addPlayerProjectile(std::unique_ptr<Projectile>&& projectile) {
    if (projectile) {
        player_projectiles_.push_back(std::move(projectile));
    }
}

void ProjectileManager::addEnemyProjectile(std::unique_ptr<Projectile>&& projectile) {
    if (projectile) {
        enemy_projectiles_.push_back(std::move(projectile));
    }
}

void ProjectileManager::render(sf::RenderWindow& window) {
    auto is_not_disabled = [](const std::unique_ptr<Projectile>& obj_ptr) {
        return !(obj_ptr->isDisabled());
        };
    for (auto& player_projectile : player_projectiles_
        | std::views::filter(is_not_disabled)) {
        player_projectile->render(window);
    }
    for (auto& enemy_projectile : enemy_projectiles_
        | std::views::filter(is_not_disabled)) {
        enemy_projectile->render(window);
    }
}

const std::vector <std::unique_ptr<Projectile>>& ProjectileManager::getPlayerProjectiles() {
    return player_projectiles_;
}

const std::vector <std::unique_ptr<Projectile>>& ProjectileManager::getEnemyProjectiles() {
    return enemy_projectiles_;
}