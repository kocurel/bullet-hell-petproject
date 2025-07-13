#pragma once
/// @file Enemy2.h
/// @brief declares the Enemy2 class that derives from Enemy base class
#pragma once
#include "Enemy.h"

#include "ProjectileBuilder.h"
#include "SeriesInLinePattern.h"
#include "TripleStraightPattern.h"
#include "UpwardSprayPattern.h"

/// @brief An Enemy subclass
/// @sa IAttackPattern, Enemy
class Enemy2 : public Enemy, private UpwardSprayPattern {
protected:
    /// @brief The current attack pattern. Used for switching up attack patterns.
    int pattern_ = 0;
    /// @brief Used for horizontal movement.
    bool going_left_ = 0;
    /// @brief Defines attack behaviour of Enemy2.
    /// Calls choosePattern() whenever an attack pattern finishes
    /// @param player - a reference to the Player object.
    /// @param projectiles - a reference to the IAddProjectiles interface of ProjectileManager
    /// @sa choosePattern, IAttackPattern, Player, IAddProjectiles
    void attack(IPlayer& player, IProjectileManager& projectiles) override;
public:
    /// @brief An explicit constructor
    /// @param projectiles - a reference to the Interface of the Projectile Manager. 
    explicit Enemy2(IProjectileManager& projectiles);

    /// @brief The main process method of Enemy2.
    /// should get called each frame.
    /// @param player - a reference to the Player object.
    void process(IPlayer& player) override;
};