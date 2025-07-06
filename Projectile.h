/// @file Projectile.h
/// @brief declares the abstract base class Projectile
#pragma once

#include "CollisionCircle.h"
#include "SpriteOwner.h"
#include <unordered_map>
#include <SFML/Graphics.hpp> 

// Forward declaration
class IAddProjectile;

/// @brief Base class for all projectiles in the game.
///
/// Projectiles are objects that move, can deal damage, and have a hitbox for collision detection.
/// This class provides common properties and methods for all projectile types,
/// and declares pure virtual functions that must be implemented by derived classes.
class Projectile : public SpriteOwner {
protected:
    /// @brief Reference to an interface for adding new projectiles.
    /// This allows projectiles to potentially create other projectiles (e.g., on hit, or for special attacks).
    IAddProjectile& projectiles_;

    /// @brief The current position of the projectile in game coordinates.
    sf::Vector2f position_;

    /// @brief The normalized direction vector of the projectile's movement.
    sf::Vector2f direction_;

    /// @brief Constructor for the Projectile base class.
    /// @param projectiles - a reference to an IAddProjectile interface.
    explicit Projectile(IAddProjectile& projectiles);

    /// @brief The circular hitbox used for collision detection.
    CollisionCircle hitbox_;

    /// @brief The amount of damage this projectile deals upon impact.
    float damage_ = 3.f;

    /// @brief The scaling factor applied to the projectile's sprite.
    float scale_ = 1.f;

    /// @brief The current velocity (speed) of the projectile.
    float velocity_ = 3.f;

    /// @brief The maximum allowed velocity for the projectile.
    float max_velocity_ = 1000000.f; // A very large number, effectively no limit by default

public:
    /// @brief Virtual destructor to ensure proper cleanup of derived Projectile types.
    virtual ~Projectile() = default;

    /// @brief Pure virtual method to define the specific processing logic for each projectile type.
    /// Derived classes must implement this method.
    virtual void process() = 0;

    /// @brief Gets a constant reference to the projectile's hitbox.
    /// @return A const reference to the CollisionCircle representing the projectile's hitbox.
    const CollisionCircle& getHitbox() const;

    /// @brief Gets the damage value of the projectile.
    /// @return A float representing the projectile's damage.
    float getDamage() const;

    /// @brief Sets the scaling factor for the projectile's sprite.
    /// @param scale The new float scaling factor.
    void setScale(float scale);

    /// @brief Sets the movement direction of the projectile.
    /// The input vector will be normalized.
    /// @param direction An sf::Vector2f representing the new direction.
    void setDirection(sf::Vector2f direction);

    /// @brief Sets the damage value of the projectile.
    /// @param damage The new float damage value.
    void setDamage(float damage);

    /// @brief Sets the velocity (speed) of the projectile.
    /// @param velocity The new float velocity value.
    void setVelocity(float velocity);

    /// @brief Moves the projectile by a given displacement vector.
    /// Updates both the sprite and hitbox positions.
    /// @param displacement An sf::Vector2f representing the amount to move.
    void move(sf::Vector2f displacement);

    /// @brief Sets the absolute position of the projectile.
    /// Updates both the sprite and hitbox positions.
    /// @param position The new sf::Vector2f position.
    void setPosition(sf::Vector2f position);

    /// @brief Sets the maximum velocity for the projectile.
    /// @param max_velocity The new float maximum velocity.
    void setMaxVelocity(float max_velocity);

    /// @brief Sets the color tint of the projectile's sprite.
    /// @param color The new sf::Color to apply.
    void setColor(sf::Color color);
};

/// @brief Rotates a 2D vector by a specified angle in degrees.
///
/// This function uses a static unordered_map to cache sine and cosine values
/// for frequently used angles, improving performance for repeated rotations.
/// The angle is rounded to two decimal places for caching.
/// @param vec - The sf::Vector2f to rotate.
/// @param angle_deg - The angle in degrees by which to rotate the vector.
/// @return An sf::Vector2f representing the rotated vector.
sf::Vector2f rotateVector(const sf::Vector2f& vec, float angle_deg);
