/// @file Enemy.h
/// @brief declares the abstract base class of all Enemy types
#pragma once
#include "SpriteOwner.h"
#include "Positionable.h"
#include "CollisionCircle.h"

// forward declarations
class IPickupManager;
class IProjectileManager;
class IPlayer;
class Projectile;

/// @brief Abstract base class for all Enemy types.
class Enemy : public SpriteOwner , public virtual Positionable {
protected:
    /// @brief A reference to the projectile manager.
    IProjectileManager& projectile_manager_;
    /// @brief The class constructor.
    /// @param projectiles - reference to the IProjectileManager interface for projectile_manager_.
    Enemy(IProjectileManager& projectiles);
    /// @brief Enemy's health_points.
    float health_ = 10;
public:
    /// @brief The default copy constructor.
    /// @param other - a reference to the other Enemy object.
    Enemy(Enemy& other) = default;

    /// @brief Enemy's hitbox
    CollisionCircle hitbox_;

    /// @brief Pure virtual method, defines Enemy's behaviour in each game frame.
    /// @param player - a reference to the Player object
    virtual void process(IPlayer& player) = 0;

    /// @brief Virtual method, defines the behaviour, when Enemy's health reaches 0.
    void onDestruction(IPickupManager& pickups); 

    /// @brief Applies damage of a Projectile to the Enemy,
    /// disables the projectiles and checks if the Enemy has no health_points.
    /// In that case it calls onDestruction() and disable().
    /// @param projectile - a reference to the projectile that hit the Enemy.
    /// @param pickups - a reference to the PickupManager to be passed to onDestruction().
    void hit(Projectile& projectile, IPickupManager& pickups);

    /// @brief Checks hitboxes by calling CollisionCircle::checkCollision on
    /// Enemy's and Projectile's hitboxes. Calls hit(Projectile&),
    /// when a collision is detected.
    /// @param projectile - a reference to the Projectile object for collision check.
    /// @param pickups - a reference to the Pickup Manager to be passed to hit().
    void checkCollision(Projectile& projectile, IPickupManager& pickups);

    /// @brief The default virtual destructor
    virtual ~Enemy() = default;
};