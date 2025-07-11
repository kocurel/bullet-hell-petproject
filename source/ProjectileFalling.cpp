#include "ProjectileFalling.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"

ProjectileFalling::ProjectileFalling(IProjectileManager& projectiles, const float scaling)
    : Projectile(projectiles) {
    sprite_.setOrigin({ 32.f, 32.f });
    sprite_.setTexture(TextureManager::getInstance().getTexture("assets/circle64.png"));
    sprite_.scale({ 0.5f * scaling, 0.5f * scaling });
    hitbox_.radius_ = 16.f * scaling;
}

void ProjectileFalling::process() {
    direction_ = (direction_ + sf::Vector2f{ 0,1 } * 0.03f);
    if (direction_.lengthSquared() > 1) {
        direction_ = direction_.normalized();
    }
    move(direction_*velocity_);
    if (position_.y > 900 || position_.y < -500 || position_.x < 0 || position_.x > 1200) {
        disable();
    }
}