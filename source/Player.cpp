#include "Player.h"
#include "IPickupManager.h"
#include "ProjectileStraight.h"
#include "ProjectileBuilder.h"
#include "UserInterface.h"
#include "IProjectileManager.h"
#include "TextureManager.h"
#include "InputManager.h"
#include <algorithm>
#include <numbers>
#include "ProjectileFactory.h"

Player::Player(IProjectileManager& projectile_manager) : projectile_manager_(projectile_manager) {
    sprite_.setTexture(TextureManager::getInstance().getTexture("assets/circle64.png"));
    sprite_.setOrigin({ 32.f, 32.f });
    sprite_.scale({ 0.5f, 0.5f });
    sprite_.setColor(sf::Color(0, 255, 100, 255));
    hitbox_.radius_ = 4.f;
}

const CollisionCircle& Player::getHitbox() const {
    return hitbox_;
}

void Player::hit(Projectile& projectile) {
    i_frames_ = 30;
    --health_points_;
    UserInterface::getInstance().updateLife(health_points_);
}

void Player::attack(IProjectileManager& projectiles) const {
    std::unique_ptr<Projectile> projectile;
    if (attack_pattern_ % 2 == 0) {
        projectile = ProjectileFactory::createProjectile(ProjectileType::ProjectileStraight, 
            projectiles, position_, { 0, -1 }, bullet_speed_, 0.75f, { 255, 255, 255, 168 });
        projectiles.addPlayerProjectile(std::move(projectile));
    }

    for (int i = 0; i < (attack_pattern_ + 1) /2; i++) {
        float space_in_the_middle = 0;
        if (attack_pattern_ % 2 == 0) {
            space_in_the_middle = 8.f;
        }
        sf::Vector2f pos = (position_ - sf::Vector2f(float(i + 1) * 16 + space_in_the_middle - 8.f, 0));
        projectile = ProjectileFactory::createProjectile(ProjectileType::ProjectileStraight,
            projectiles, pos, { 0, -1 }, bullet_speed_, 0.75f, { 255, 255, 255, 168 });
        projectiles.addPlayerProjectile(std::move(projectile));
        
        pos = (position_ + sf::Vector2f(float(i + 1) * 16 + space_in_the_middle - 8.f, 0));
        projectile = ProjectileFactory::createProjectile(ProjectileType::ProjectileStraight,
            projectiles, pos, { 0, -1 }, bullet_speed_, 0.75f, { 255, 255, 255, 168 });
        projectiles.addPlayerProjectile(std::move(projectile));
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

 bool Player::isInvincible() const {
     return (i_frames_ > 0);
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

void Player::process(IProjectileManager& projectiles, IPickupManager& pickups) {
    move();
    if (i_frames_ > 0) {
        --i_frames_;
    }
    if (bomb_timer_ > 0) {
        --bomb_timer_;
    }
    if (--attack_timer_ <= 0) {
        attack_timer_ = attack_cooldown_;
        attack(projectiles);
    }
    bool bomb_pressed = InputManager::getInstance().isKeyJustPressed(sf::Keyboard::Key::X)
        || InputManager::getInstance().isKeyJustPressed(sf::Keyboard::Key::Space);
    if (bomb_pressed && bomb_timer_ == 0 && bombs_ > 0) {
        bomb_timer_ = bomb_cooldown_;
        --bombs_;
        UserInterface::getInstance().updateBombs(bombs_);
        projectiles.clear();
    }
}