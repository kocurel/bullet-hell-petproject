#include "NewProjectile.h"
#include "ProjectileManager.h"
#include "Projectile.h"

NewProjectile::NewProjectile(std::unique_ptr<Projectile>&& projectile)
    : projectile_(std::move(projectile)) {
}

void NewProjectile::onRelease(EnemyManager& enemies, ProjectileManager& projectiles) {
    projectiles.addEnemyProjectile(std::move(projectile_));
}
