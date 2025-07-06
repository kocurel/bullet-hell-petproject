/// @file TripleStraightPattern.h
/// @brief declares TripleStraightPattern attack pattern
#pragma once

#include "IAttackPattern.h"
#include <SFML/System/Vector2.hpp>

// Forward declarations
class Player;
class IAddProjectile;

/// @brief An attack pattern consisting of three projectiles shot simultaneously.
///
/// These projectiles are shot with a 30-degree rotation between them, forming a fan-like spread.
/// The pattern sets `switch_signal_` to true when the projectiles have been shot,
/// indicating the completion of this attack burst.
class TripleStraightPattern : protected virtual IAttackPattern {
protected:
    /// @brief The time (in frames) required to reload before the next triple shot can occur.
    const int reload_time_ = 80;

    /// @brief A signal flag indicating that the current burst of shots has completed.
    /// This can be used by an external manager to switch to a different attack pattern.
    bool switch_signal_ = false;

    /// @brief Counter for the remaining time until the next attack burst.
    int until_reload_ = reload_time_;

    /// @brief The speed of the projectiles fired in this pattern.
    const float bullet_speed_ = 8.f;

    /// @brief Implements the attack logic for this pattern.
    ///
    /// This method manages the cooldown for the triple shot and, when ready,
    /// creates three projectiles simultaneously with a rotational spread.
    /// @param player A reference to the Player object, used to determine the initial direction of projectiles.
    /// @param projectiles A reference to an IAddProjectile interface to create new enemy projectiles.
    void attack(Player& player, IAddProjectile& projectiles) override;
};
