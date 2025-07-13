/// @file Player.h
/// @brief declares the Player class
#pragma once
#include "CollisionCircle.h"
#include "ProjectileBuilder.h"
#include <memory>
#include <functional>
#include "IPlayer.h"

/// @brief Represents the player character in the game.
///
/// The Player class handles player movement, attacking, health,
/// collision detection with projectile_manager and pickups, and interaction
/// with various game systems like projectile_manager and the UI.
class Player : public IPlayer {
private:
    /// @brief Reference to an interface for adding projectile_manager.
    /// This allows the Player to create projectile_manager without knowing the concrete ProjectileManager implementation.
    IProjectileManager& projectile_manager_;

    /// @brief The circular hitbox used for collision detection with other game entities.
    CollisionCircle hitbox_;

    /// @brief The movement speed of the player.
    float speed_ = 6.f;
    /// @brief The speed of projectile_manager fired by the player.
    float bullet_speed_ = 18.0f;
    /// @brief The damage dealt by player projectile_manager.
    float bullet_damage_ = 3.f;
    /// @brief Base attack cooldown value.
    float attack_cooldown_ = 15.f;
    /// @brief The timer for player's primary attack.
    float attack_timer_ = attack_cooldown_;
    /// @brief Current health points of the player.
    int health_points_ = 3;
    /// @brief Invincibility frames counter after being hit.
    int i_frames_ = 0;
    /// @brief Cooldown timer for bomb usage.
    int bomb_cooldown_ = 60;
    /// @brief Cooldown timer for bomb usage.
    int bomb_timer_ = bomb_cooldown_;
    /// @brief Number of bombs the player currently has.
    int bombs_ = 3;
    /// @brief The current attack pattern level of the player.
    int attack_pattern_ = 0;


    /// @brief Handles the player's attack logic, creating projectile_manager based on current attack pattern.
    /// @param projectile_manager A reference to the ProjectileManager manager to add new projectile_manager to.
    void attack(IProjectileManager& projectiles) const;

    /// @brief Handles the player's movement based on keyboard input.
    void move();

public:
    /// @brief Handles the event when the player is hit by a projectile.
    /// @param projectile A reference to the Projectile that hit the player.
    void hit(Projectile& projectile) override;

    /// @brief Hitbox's getter.
    /// @return Const reference to the CollisionCircle hitbox.
    const CollisionCircle& getHitbox() const override;

    /// @brief Checks whether the Player is currently invincible.
    /// @return True if the Player currently has more than 0 i_frames left.
    bool isInvincible() const override;

    /// @brief Increases the number of bombs the player has, up to a maximum.
    void increaseBomb() override;

    /// @brief Decreases the player's attack cooldown, effectively increasing attack speed.
    void AttackSpeedUp() override;

    /// @brief Increases the player's health points, up to a maximum.
    void increaseHealth() override;

    /// @brief Advances the player's attack pattern to the next level.
    void nextAttackPattern() override;

    /// @brief Resets the player's health and bomb count to their initial values.
    void resetPlayer() override;

    /// @brief Sets the player's position in game coordinates.
    /// @param position The new sf::Vector2f position for the player.
    void setPosition(sf::Vector2f position) override;

    /// @brief Gets the current health points of the player.
    /// @return An integer representing the player's current health.
    int getHealthPoints() const override;

    /// @brief Constructor for the Player class.
    /// @param projectile_manager A reference to the projectile_manager, used for adding player-fired projectile_manager.
    explicit Player(IProjectileManager& projectile_manager);

    /// @brief Processes the player's game logic for the current frame.
    ///
    /// This includes handling invincibility frames, movement, attacking,
    /// bomb usage, and collision detection with enemy projectile_manager and pickups.
    /// @param projectile_manager - a reference to the ProjectileManager manager for bomb effect.
    /// @param pickups - a reference to the PickupManager for pickup collision.
    void process(IProjectileManager& projectile_manager, IPickupManager& pickups) override;
};