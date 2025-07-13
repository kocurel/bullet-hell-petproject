#include "ProjectileStraight.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"

ProjectileStraight::ProjectileStraight(IProjectileManager& projectiles, sf::Vector2f pos, sf::Vector2f dir,
    float velocity, float scaling, sf::Color color)
    : Projectile(projectiles) {
    sprite_.setOrigin({ 32.f, 32.f });
    sprite_.setTexture(TextureManager::getInstance().getTexture("assets/circle64.png"));
    sprite_.scale({ 0.5f * scaling, 0.5f * scaling });
    hitbox_.radius_ = 16.f * scaling;
    setPosition(pos);
    setDirection(dir);
    setColor(color);
    setVelocity(velocity);
}

void ProjectileStraight::process() {
    move(direction_ * velocity_);
    if (position_.y > 900 || position_.y < -500 || position_.x < 0 || position_.x > 1200) {
        disable();
    }
}