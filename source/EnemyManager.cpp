#include "EnemyManager.h"

#include "Enemy.h"
#include "IEventManager.h"
#include "Projectile.h"
#include "IProjectileManager.h"
#include "IPickupManager.h"
#include <algorithm>
#include <ranges>

EnemyManager::EnemyManager(IEventManager& wave_controller)
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
void EnemyManager::process(IPlayer& player, IProjectileManager& projectiles, IPickupManager& pickups) {
    cleanupEnemies();
    checkWave();
    for (auto& enemy : enemies_
        | std::views::filter(is_enemy_not_disabled)) {
        enemy->process(player);
        //for (auto& projectile : projectiles.getPlayerProjectiles()
        //    | std::views::filter(is_projectile_not_disabled)) {
        //    enemy->checkCollision(*projectile, pickups);
        //}
    }
}

void EnemyManager::createEnemy(std::unique_ptr<Enemy>&& enemy) {
    enemies_.push_back(std::move(enemy));
}

void EnemyManager::clear() {
    enemies_.clear();
}

void EnemyManager::render(sf::RenderWindow& window) const {
    for (auto& enemy : enemies_
        | std::views::filter(is_enemy_not_disabled)) {
        enemy->render(window);
    }
}
const std::vector<std::unique_ptr<Enemy>>& EnemyManager::getEnemies() const {
    return enemies_;
}
EnemyManager::~EnemyManager() = default;