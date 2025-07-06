#include "NewEnemy.h"
#include "EnemyManager.h"
#include "Enemy.h"

NewEnemy::NewEnemy(std::unique_ptr<Enemy>&& enemy) : _enemy(std::move(enemy)) {
}

void NewEnemy::onRelease(EnemyManager& enemies, ProjectileManager& projectiles) {
    enemies.createEnemy(std::move(_enemy));
}