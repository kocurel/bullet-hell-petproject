#include "Enemy1.h"
#include "ProjectileStraight.h"
#include "ProjectileBuilder.h"
#include "Player.h"
#include "IAddProjectile.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
#include "RandomNumberGenerator.h"

Enemy1::Enemy1(IAddProjectile& projectiles) : Enemy(projectiles) {
    sprite_.setOrigin(sf::Vector2f(32.f, 32.f));
    sprite_.setTexture(TextureManager::getInstance().getTexture("assets/circle64.png"));
    position_ = sf::Vector2f(450.f, -100.f);
    sprite_.setPosition(position_);
    sprite_.setColor(sf::Color(200, 100, 60, 255));
    sprite_.setScale({ 0.75f, 0.75f });
    hitbox_.position_ = position_;
    hitbox_.radius_ = 18.f;
    health_ = 10.f;
}

void Enemy1::choosePattern() {
    float uniform = RandomNumberGenerator::getInstance().uniformRange(0.f, 1.f);
    float pattern0_chance = 0.5f;
    float pattern1_chance = 0.4f;
    float pattern2_chance = 0.5f;
    switch (pattern_) {
    case 0:
        pattern1_chance = 0.4f;
        pattern2_chance = 0.5f;
        if (uniform < pattern1_chance) {
            pattern_ = 1;
        }
        else if (uniform < pattern1_chance + pattern2_chance) {
            pattern_ = 2;
        }
        break;
    case 1:
        pattern0_chance = 0.3f;
        pattern2_chance = 0.5f;
        if (uniform < pattern0_chance) {
            pattern_ = 0;
        }
        else if (uniform < pattern0_chance + pattern2_chance) {
            pattern_ = 2;
        }
        break;
    case 2:
        pattern0_chance = 0.3f;
        pattern1_chance = 0.5f;
        if (uniform < pattern0_chance) {
            pattern_ = 0;
        }
        else if (uniform > pattern0_chance + pattern1_chance) {
            pattern_ = 1;
        }
        break;
    }
}

void Enemy1::attack(Player& player, IAddProjectile& projectiles_) {
    switch (pattern_) {
    case 0:
        UpwardSprayPattern::attack(player, projectiles_);
        if (UpwardSprayPattern::switch_signal_) {
            choosePattern();
            UpwardSprayPattern::switch_signal_ = false;
        }
        break;
    case 1:
        SeriesInLinePattern::attack(player, projectiles_);
        if (SeriesInLinePattern::switch_signal_) {
            choosePattern();
            SeriesInLinePattern::switch_signal_ = false;
        }
        break;
    case 2:
        TripleStraightPattern::attack(player, projectiles_);
        if (TripleStraightPattern::switch_signal_) {
            choosePattern();
            TripleStraightPattern::switch_signal_ = false;
        }
        break;
    }
}

void Enemy1::process(Player& player) {
    bool getting_into_position = position_.y < 50;
    if (getting_into_position) {
        position_ += sf::Vector2f(0.f, 1.f) * 3.f;
        hitbox_.position_ = position_;
        sprite_.setPosition(position_);
        return;
    }
    if (going_left_) {
        position_ += sf::Vector2f(-1.f, 0.f) * 3.f + sf::Vector2f(0.f, 1.f) * 0.5f;
        if (position_.x < 200.f) {
            going_left_ = false;
        }
    }
    else {
        position_ += sf::Vector2f(1.f, 0.f) * 3.f + sf::Vector2f(0.f, 1.f) * 0.5f;
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