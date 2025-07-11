#include "ProjecitleWavy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"

ProjecitleWavy::ProjecitleWavy(IProjectileManager& projectiles, const float scaling)
    : Projectile(projectiles) {
    sprite_.setOrigin({ 32.f, 32.f });
    sprite_.setTexture(TextureManager::getInstance().getTexture("assets/circle64.png"));
    sprite_.scale({ 0.5f * scaling, 0.5f * scaling });
    hitbox_.radius_ = 16.f * scaling;
}

void ProjecitleWavy::process() {
    direction_ = rotateVector(direction_, 0.5);
    move(direction_ * velocity_);
    if (position_.y > 900 || position_.y < -500 || position_.x < 0 || position_.x > 1200) {
        disable();
    }
}