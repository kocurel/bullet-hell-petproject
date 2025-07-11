#include "Player.h"

#include "PickupManager.h"
#include "ProjectileManager.h"
#include "ProjectileStraight.h"
#include "ProjectileBuilder.h"
#include "UserInterface.h"
#include "IProjectileManager.h"
#include "Projectile.h"
#include <SFML/Window.hpp>
#include "SpriteOwner.h"
#include "TextureManager.h"
#include "InputManager.h"
#include <algorithm>
#include <ranges>
#include <iostream>
#include <numbers>

Player::Player(IProjectileManager& projectiles) : projectiles_(projectiles) {
    sprite_.setTexture(TextureManager::getInstance().getTexture("assets/circle64.png"));
    sprite_.setOrigin({ 32.f, 32.f });
    sprite_.scale({ 0.5f, 0.5f });
    sprite_.setColor(sf::Color(0, 255, 100, 255));
    hitbox_.radius_ = 4.f;
}

void Player::hit(Projectile& projectile) {
    projectile.disable();
    --health_points_;
    UserInterface::getInstance().updateLife(health_points_);
}

void Player::attack(IProjectileManager& projectiles) const {
    std::unique_ptr<Projectile> projectile;
    ProjectileBuilder<ProjectileStraight> ps_builder(projectiles_);
    if (attack_pattern_ % 2 == 0) {
        ps_builder.color({ 255, 255, 255, 168 })
            .damage(bullet_damage_)
            .direction({ 0.f, -1.f })
            .position(position_)
            .velocity(bullet_speed_);
        projectile = ps_builder.build();
        projectiles.createPlayerProjectile(std::move(projectile));
    }

    for (int i = 0; i < (attack_pattern_ + 1) /2; i++) {
        float space_in_the_middle = 0;
        if (attack_pattern_ % 2 == 0) {
            space_in_the_middle = 8.f;
        }
        ps_builder.color({ 255, 255, 255, 168 })
            .damage(bullet_damage_)
            .direction({ 0.f, -1.f })
            .position(position_ - sf::Vector2f(float(i+1)*16 + space_in_the_middle - 8.f, 0))
            .velocity(bullet_speed_);
        projectile = ps_builder.build();
        projectiles.createPlayerProjectile(std::move(projectile));
        ps_builder.position(position_ + sf::Vector2f(float(i+1)*16 + space_in_the_middle - 8.f, 0));
        projectile = ps_builder.build();
        projectiles.createPlayerProjectile(std::move(projectile));
    }
}

void Player::move() {
    int left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    int right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    int up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    int down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    float horizontal = (right - left) * speed_;
    float vertical = (down - up) * speed_;
    // handle diagonal movement speed
    if (horizontal * vertical) {
        static constexpr float one_over_sqrt2 = 1.0f / std::numbers::sqrt2_v<float>;
        vertical *= one_over_sqrt2;
        horizontal *= one_over_sqrt2;
    }
    position_.x += horizontal;
    position_.y += vertical;
    if (position_.y > 820 - 16) {
        position_.y = 820 - 16;
    }
    if (position_.y < 20 + 16) {
        position_.y = 20 + 16;
    }
    if (position_.x > 750 - 16) {
        position_.x = 750 - 16;
    }
    if (position_.x < 150 + 16) {
        position_.x = 150 + 16;
    }
    sprite_.setPosition(position_);
    hitbox_.position_ = position_;
}

 void Player::setPosition(sf::Vector2f position) {
    position_ = position;
    sprite_.setPosition(position_);
    hitbox_.position_ = position_;
}

 void Player::increaseHealth() {
     if (health_points_ < 3) {
         ++health_points_;
         UserInterface::getInstance().updateLife(health_points_);
     }
 }
 void Player::nextAttackPattern() {
     attack_cooldown_ *= float(attack_pattern_ + 2) / (attack_pattern_ + 1);
    ++attack_pattern_;
    AttackSpeedUp();
 }
 void Player::AttackSpeedUp() {
     attack_cooldown_ *= 0.975f;
 }

 void Player::increaseBomb() {
     if (bombs_ < 3) {
         ++bombs_;
         UserInterface::getInstance().updateBombs(bombs_);
     }
 }
 int Player::getHealthPoints() const {
     return health_points_;
 }

 void Player::resetPlayer() {
     health_points_ = 3;
     bombs_ = 3;
     attack_pattern_ = 0;
     attack_cooldown_ = 15;
     UserInterface::getInstance().updateBombs(bombs_);
     UserInterface::getInstance().updateLife(health_points_);
 }

void Player::process(ProjectileManager& projectiles, PickupManager& pickups) {
    if (i_frames_ > 0) {
        --i_frames_;
    }
    move();
    if (--cooldown_ <= 0) {
        cooldown_ = attack_cooldown_;
        attack(projectiles);
    }
    bool bomb_pressed = InputManager::getInstance().isKeyJustPressed(sf::Keyboard::Key::X)
        || InputManager::getInstance().isKeyJustPressed(sf::Keyboard::Key::Space);
    if (--bomb_cooldown <= 0 && bomb_pressed && bombs_ > 0) {
        bomb_cooldown = 60;
        --bombs_;
        UserInterface::getInstance().updateBombs(bombs_);
        projectiles.clear();
    }

    for (auto& projectile : projectiles.getEnemyProjectiles()
        | std::views::filter([](const std::unique_ptr<Projectile>& obj) { return !obj->isDisabled(); })) {
        bool collided = hitbox_.checkCollision(projectile->getHitbox());
        if (i_frames_ > 0) {
            break;
        }
        if (collided) {
            i_frames_ = 30;
            hit(*projectile);
        }
    }/*
    for (auto& pickup : pickups.getPickups()
        | std::views::filter([](const std::unique_ptr<Pickup>& obj) { return !obj->isDisabled(); })) {
        bool collided = hitbox_.checkCollision(pickup->getHitbox());

        if (collided) {
            pickup->onPickup(*this);
            UserInterface::getInstance().increaseScore(20);
        }
    }*/
}