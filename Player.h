/// @file Player.h
/// @brief declares the Player class
#pragma once
#include "SpriteOwner.h"
#include "CollisionCircle.h"
#include "ProjectileBuilder.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include "Positionable.h"

// forward declarations
class IAddProjectile;
class ProjectileManager;
class Projectile;
class ProjectileStraight;
class UserInterface;
class PickupManager;

/// @brief Represents the player character in the game.
///
/// The Player class handles player movement, attacking, health,
/// collision detection with projectiles and pickups, and interaction
/// with various game systems like projectiles and the UI.
class Player : public SpriteOwner, public Positionable {
private:
    /// @brief Reference to an interface for adding projectiles.
    /// This allows the Player to create projectiles without knowing the concrete ProjectileManager implementation.
    IAddProjectile& projectiles_;

    /// @brief The circular hitbox used for collision detection with other game entities.
    CollisionCircle hitbox_;

    /// @brief The movement speed of the player.
    float speed_ = 6.f;
    /// @brief The speed of projectiles fired by the player.
    float bullet_speed_ = 18.0f;
    /// @brief The damage dealt by player projectiles.
    float bullet_damage_ = 3.f;
    /// @brief Cooldown timer for player's primary attack.
    float cooldown_ = 0;
    /// @brief Base attack cooldown value.
    float attack_cooldown_ = 15.f;
    /// @brief Current health points of the player.
    int health_points_ = 3;
    /// @brief Invincibility frames counter after being hit.
    int i_frames_ = 0;
    /// @brief Cooldown timer for bomb usage.
    int bomb_cooldown = 0;
    /// @brief Number of bombs the player currently has.
    int bombs_ = 3;
    /// @brief The current attack pattern level of the player.
    int attack_pattern_ = 0;

    /// @brief Handles the event when the player is hit by a projectile.
    /// @param projectile A reference to the Projectile that hit the player.
    void hit(Projectile& projectile);

    /// @brief Handles the player's attack logic, creating projectiles based on current attack pattern.
    /// @param projectiles A reference to the ProjectileManager manager to add new projectiles to.
    void attack(ProjectileManager& projectiles) const;

    /// @brief Handles the player's movement based on keyboard input.
    void move();

public:
    /// @brief Increases the number of bombs the player has, up to a maximum.
    void increaseBomb();

    /// @brief Decreases the player's attack cooldown, effectively increasing attack speed.
    void AttackSpeedUp();

    /// @brief Increases the player's health points, up to a maximum.
    void increaseHealth();

    /// @brief Advances the player's attack pattern to the next level.
    void nextAttackPattern();

    /// @brief Resets the player's health and bomb count to their initial values.
    void resetPlayer();

    /// @brief Sets the player's position in game coordinates.
    /// @param position The new sf::Vector2f position for the player.
    void setPosition(sf::Vector2f position);

    /// @brief Gets the current health points of the player.
    /// @return An integer representing the player's current health.
    int getHealthPoints() const;

    /// @brief Constructor for the Player class.
    /// @param projectiles A reference to an IAddProjectile interface, used for adding player-fired projectiles.
    explicit Player(IAddProjectile& projectiles);

    /// @brief Processes the player's game logic for the current frame.
    ///
    /// This includes handling invincibility frames, movement, attacking,
    /// bomb usage, and collision detection with enemy projectiles and pickups.
    /// @param projectiles - a reference to the ProjectileManager manager for enemy projectile collision.
    /// @param pickups - a reference to the PickupManager for pickup collision.
    void process(ProjectileManager& projectiles, PickupManager& pickups);
};