#include "EnemyManager.h"

#include "Enemy.h"
#include "INotifyEndWave.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include <algorithm>
#include <mutex>
#include <ranges>

EnemyManager::EnemyManager(INotifyEndWave& wave_controller)
    : wave_controller_(wave_controller),
    is_enemy_disabled([](const std::unique_ptr<Enemy>& obj) { return obj->isDisabled(); }),
    is_enemy_not_disabled([](const std::unique_ptr<Enemy>& obj) { return !obj->isDisabled(); }),
    is_projectile_not_disabled([](const std::unique_ptr<Projectile>& obj) { return !obj->isDisabled(); })
{
}

void EnemyManager::cleanupEnemies() {
    if (--cleanup_counter_ <= 0) {
        cleanup_counter_ = 360;
        auto it = std::remove_if(enemies_.begin(), enemies_.end(), is_enemy_disabled);
        enemies_.erase(it, enemies_.end());
    }
}
void EnemyManager::checkWave() {
    if (--wave_counter_ <= 0) {
        wave_counter_ = 30;
        auto count = std::count_if(enemies_.begin(), enemies_.end(), is_enemy_not_disabled);
        if (count == 0) {
            wave_controller_.endWave();
        }
    }
}

void EnemyManager::process(Player& player, ProjectileManager& projectiles, PickupManager& pickups) {
    cleanupEnemies();
    checkWave();
    for (auto& enemy : enemies_
        | std::views::filter(is_enemy_not_disabled)) {
        enemy->process(player);
        std::lock_guard lck(projectiles.getPlayerMtx());
        for (auto& projectile : projectiles.getPlayerProjectiles()
            | std::views::filter(is_projectile_not_disabled)) {
            enemy->checkCollision(*projectile, pickups);
        }
    }
}

void EnemyManager::createEnemy(std::unique_ptr<Enemy>&& enemy) {
    enemies_.push_back(std::move(enemy));
}

void EnemyManager::clearEnemies() {
    enemies_.clear();
}

void EnemyManager::renderEnemies(sf::RenderWindow& window) {
    for (auto& enemy : enemies_
        | std::views::filter(is_enemy_not_disabled)) {
        enemy->render(window);
    }
}
EnemyManager::~EnemyManager() = default;