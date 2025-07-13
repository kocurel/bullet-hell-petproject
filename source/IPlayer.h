#pragma once
#include "Positionable.h"
#include "SpriteOwner.h"

class IProjectileManager;
class IPickupManager;
class Projectile;

class IPlayer: public SpriteOwner, public Positionable {
public:
    /// @brief Handles the event when the player is hit by a projectile.
    /// @param projectile A reference to the Projectile that hit the player.
    virtual void hit(Projectile& projectile) = 0;

    /// @brief Hitbox's getter.
    /// @return Const reference to the CollisionCircle hitbox.
    virtual const CollisionCircle& getHitbox() const = 0;

    /// @brief Checks whether the Player is currently invincible.
    /// @return True if the Player currently has more than 0 i_frames left.
    virtual bool isInvincible() const = 0;

    /// @brief Increases the number of bombs the player has, up to a maximum.
    virtual void increaseBomb() = 0;

    /// @brief Decreases the player's attack cooldown, effectively increasing attack speed.
    virtual void AttackSpeedUp() = 0;

    /// @brief Increases the player's health points, up to a maximum.
    virtual void increaseHealth() = 0;

    /// @brief Advances the player's attack pattern to the next level.
    virtual void nextAttackPattern() = 0;

    /// @brief Resets the player's health and bomb count to their initial values.
    virtual void resetPlayer() = 0;

    /// @brief Sets the player's position in game coordinates.
    /// @param position The new sf::Vector2f position for the player.
    virtual void setPosition(sf::Vector2f position) = 0;

    /// @brief Gets the current health points of the player.
    /// @return An integer representing the player's current health.
    virtual int getHealthPoints() const = 0;

    /// @brief Processes the player's game logic for the current frame.
    ///
    /// This includes handling invincibility frames, movement, attacking,
    /// bomb usage, and collision detection with enemy projectiles and pickups.
    /// @param projectiles - a reference to the projectile manager for enemy projectile collision.
    /// @param pickups - a reference to the pickup manager for pickup collision.
    virtual void process(IProjectileManager& projectiles, IPickupManager& pickups) = 0;
};