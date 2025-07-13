#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include "IProjectileManager.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "IPlayer.h"
#include "UserInterface.h"
#include "IPickupManager.h"
#include "RandomNumberGenerator.h"
#include "PickupFactory.h"

Enemy::Enemy(IProjectileManager& projectiles) : projectile_manager_(projectiles) {
}

void Enemy::onDestruction(IPickupManager& pickups) {
    UserInterface::getInstance().increaseScore(10);
    float uniform = RandomNumberGenerator::getInstance().uniformRange(0.f, 1.f);
    if (uniform < 0.05) {
        pickups.createPickup(PickupFactory::createPickup(PickupType::AttackPattern, position_));
    }
    else if (uniform < 0.10) {
        pickups.createPickup(PickupFactory::createPickup(PickupType::Health, position_));
    }
    else if (uniform < 0.15) {
        pickups.createPickup(PickupFactory::createPickup(PickupType::Bomb, position_));
    }
    else if (uniform < 0.50) {
        pickups.createPickup(PickupFactory::createPickup(PickupType::AttackUp, position_));
    }
    return;
}

void Enemy::hit(Projectile& projectile, IPickupManager& pickups) {
    health_ -= projectile.getDamage();
    if (health_ <= 0.1f) {
        onDestruction(pickups);
        disable();
    }
}

void Enemy::checkCollision(Projectile& projectile, IPickupManager& pickups) {
    bool collides = projectile.getHitbox().checkCollision(hitbox_);
    if (collides) {
        hit(projectile, pickups);
    }
}
