#include "ProjectileManager.h"

#include "Projectile.h"
#include <algorithm>
#include <ranges>
#include <iostream>

ProjectileManager::ProjectileManager()
          : is_not_disabled([](const std::unique_ptr<Projectile>& proj) { return !(proj->isDisabled()); }),
            is_disabled([](const std::unique_ptr<Projectile>& proj) { return (proj->isDisabled()); }) {
}

void ProjectileManager::clearProjectiles() {
    std::lock_guard enemy_lck(enemy_mtx_);
    std::lock_guard player_lck(player_mtx_);
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

void ProjectileManager::process() {
    cleanupProjectiles();
    for (auto& enemy_projectile : enemy_projectiles_
        | std::views::filter(is_not_disabled)) {
        enemy_projectile->process();
    }
    for (auto& player_projectile : player_projectiles_
        | std::views::filter(is_not_disabled)) {
        player_projectile->process();
    }
}

void ProjectileManager::createPlayerProjectile(std::unique_ptr<Projectile>&& projectile) {
    std::lock_guard lck(player_mtx_);
    player_projectiles_.push_back(std::move(projectile));
}

void ProjectileManager::createEnemyProjectile(std::unique_ptr<Projectile>&& projectile) {
    std::lock_guard lck(enemy_mtx_);
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

std::mutex& ProjectileManager::getEnemyMtx() {
    return enemy_mtx_;
}

std::mutex& ProjectileManager::getPlayerMtx() {
    return player_mtx_;
}

const std::vector <std::unique_ptr<Projectile>>& ProjectileManager::getPlayerProjectiles() {
    return player_projectiles_;
}

const std::vector <std::unique_ptr<Projectile>>& ProjectileManager::getEnemyProjectiles() {
    return enemy_projectiles_;
}