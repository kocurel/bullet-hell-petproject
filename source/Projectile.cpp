#include <SFML/Graphics.hpp>
#include "IProjectileManager.h"
#include "Projectile.h"
#include "TextureManager.h"
#include <cmath>
#include <utility>

Projectile::Projectile(IProjectileManager& projectiles) : projectiles_(projectiles) {}

const CollisionCircle& Projectile::getHitbox() const {
    return hitbox_;
}

float Projectile::getDamage() const {
    return damage_;
}

void Projectile::setScale(float scale) {
    scale_ = scale;
}

void Projectile::setDirection(sf::Vector2f direction) {
    direction_ = direction.normalized();
}

void Projectile::setDamage(float damage) {
    damage_ = damage;
}

void Projectile::setVelocity(float velocity) {
    velocity_ = velocity;
}

void Projectile::setMaxVelocity(float max_velocity) {
    max_velocity_ = max_velocity;
}


void Projectile::move(sf::Vector2f displacement) {
    position_ += displacement;
    sprite_.setPosition(position_);
    hitbox_.position_ = position_;
}

void Projectile::setPosition(sf::Vector2f position) {
    position_ = position;
    sprite_.setPosition(position_);
    hitbox_.position_ = position_;
}

void Projectile::setColor(sf::Color color) {
    sprite_.setColor(color);
}

sf::Vector2f rotateVector(const sf::Vector2f& vec, float angle_deg) {
    angle_deg = round(angle_deg * 100.f) / 100.f;
    static std::unordered_map<float, std::pair<float, float>> trig;
    float sin_angle, cos_angle;
    if (trig.contains(angle_deg)) {
        cos_angle = trig[angle_deg].first;
        sin_angle = trig[angle_deg].second;
    }
    else {
        float angle_rad = float(angle_deg) * 3.141592653f / 180;
        cos_angle = cosf(angle_rad);
        sin_angle = sinf(angle_rad);
        trig[angle_deg] = std::pair(cos_angle, sin_angle);
    }

    sf::Vector2f out = sf::Vector2f(cos_angle * vec.x - sin_angle * vec.y,
        sin_angle * vec.x + cos_angle * vec.y);
    return out;
}