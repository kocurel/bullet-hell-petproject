#include "Enemy2.h"
#include "ProjectileStraight.h"
#include "ProjectileBuilder.h"
#include "Player.h"
#include "IAddProjectile.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
#include "RandomNumberGenerator.h"

Enemy2::Enemy2(IAddProjectile& projectiles) : Enemy(projectiles) {
    sprite_.setOrigin(sf::Vector2f(32.f, 32.f));
    sprite_.setTexture(TextureManager::getInstance().getTexture("assets/circle64.png"));
    position_ = sf::Vector2f(450.f, -100.f);
    sprite_.setPosition(position_);
    sprite_.setColor(sf::Color(255, 140, 60, 255));
    sprite_.setScale({ 0.75f, 0.75f });
    hitbox_.position_ = position_;
    hitbox_.radius_ = 18.f;
    health_ = 30.f;
    setReloadTime(30);
}

void Enemy2::attack(Player& player, IAddProjectile& projectiles_) {
    UpwardSprayPattern::attack(player, projectiles_);
}

void Enemy2::process(Player& player) {
    bool getting_into_position = position_.y < 100;
    if (getting_into_position) {
        position_ += sf::Vector2f(0.f, 1.f) * 3.f;
        hitbox_.position_ = position_;
        sprite_.setPosition(position_);
        return;
    }
    if (going_left_) {
        position_ += sf::Vector2f(-1.f, 0.f) * 3.f;
        if (position_.x < 200.f) {
            going_left_ = false;
        }
    }
    else {
        position_ += sf::Vector2f(1.f, 0.f) * 3.f;
        if (position_.x > 700.f) {
            going_left_ = true;
        }
    }
    // attack
    attack(player, projectiles_);
    hitbox_.position_ = position_;
    sprite_.setPosition(position_);
    if (position_.y > 1200) {
        disable();
    }
}