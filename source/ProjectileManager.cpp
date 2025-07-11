#include "ProjectileManager.h"
#include "IEnemyManager.h"
#include "Projectile.h"
#include <algorithm>
#include <ranges>
#include <iostream>
#include "Enemy.h"

ProjectileManager::ProjectileManager()
          : is_not_disabled([](const std::unique_ptr<Projectile>& proj) { return !(proj->isDisabled()); }),
            is_disabled([](const std::unique_ptr<Projectile>& proj) { return (proj->isDisabled()); }) {
}

void ProjectileManager::clear() {
    enemy_projectiles_.clear();
    player_projectiles_.clear();
}

void ProjectileManager::cleanupProjectiles() {
    if (--cleanup_counter_ <= 0) {
        cleanup_counter_ = 120;
        auto it_enemy = std::remove_if(enemy_projectiles_.begin(), enemy_projectiles_.end(), is_disabled);
        enemy_projectiles_.erase(it_enemy, enemy_projectiles_.end());
        auto it_player = std::remove_if(player_projectiles_.begin(), player_projectiles_.end(), is_disabled);
        player_projectiles_.erase(it_player, player_projectiles_.end());
    }
}

void ProjectileManager::process(IEnemyManager& enemy_manager, Player& player, IPickupManager& pickup_manager) {
    cleanupProjectiles();
    for (auto& enemy_projectile : enemy_projectiles_
        | std::views::filter(is_not_disabled)) {
        enemy_projectile->process();
    }
    for (auto& player_projectile : player_projectiles_
        | std::views::filter(is_not_disabled)) {
        player_projectile->process();
    }
    // check collision of enemies with player projectiles
    for (auto& enemy : enemy_manager.getEnemies()
        | std::views::filter([](const std::unique_ptr<Enemy>& obj) { return !obj->isDisabled(); })) {
        if (enemy->isDisabled())
            continue;
        for (auto& projectile : player_projectiles_
            | std::views::filter(is_not_disabled)) {
            if (enemy->hitbox_.checkCollision(projectile->getHitbox())) {
                projectile->disable();
                enemy->hit(*projectile, pickup_manager);
            }
        }
    }
}

void ProjectileManager::createPlayerProjectile(std::unique_ptr<Projectile>&& projectile) {
    player_projectiles_.push_back(std::move(projectile));
}

void ProjectileManager::createEnemyProjectile(std::unique_ptr<Projectile>&& projectile) {
    enemy_projectiles_.push_back(std::move(projectile));
}

void ProjectileManager::render(sf::RenderWindow& window) {
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