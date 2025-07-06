#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include "IAddProjectile.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "UserInterface.h"
#include "PickupManager.h"
#include "RandomNumberGenerator.h"

Enemy::Enemy(IAddProjectile& projectiles) : projectiles_(projectiles) {
}

void Enemy::onDestruction(PickupManager& pickups) {
    UserInterface::getInstance().increaseScore(10);
    float uniform = RandomNumberGenerator::getInstance().uniformRange(0.f, 1.f);
    if (uniform < 0.05) {
        pickups.createPickup(3, position_);
    }
    else if (uniform < 0.10) {
        pickups.createPickup(0, position_);
    }
    else if (uniform < 0.15) {
        pickups.createPickup(2, position_);
    }
    else if (uniform < 0.50) {
        pickups.createPickup(1, position_);
    }
    return;
}

void Enemy::hit(Projectile& projectile, PickupManager& pickups) {
    projectile.disable();
    health_ -= projectile.getDamage();
    if (health_ <= 0.1f) {
        onDestruction(pickups);
        disable();
    }
}

void Enemy::checkCollision(Projectile& projectile,PickupManager& pickups) {
    bool collides = projectile.getHitbox().checkCollision(hitbox_);
    if (collides) {
        hit(projectile, pickups);
    }
}
