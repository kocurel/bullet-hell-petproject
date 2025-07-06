/// @file UpwardSprayPattern.h
/// @brief declares UpwardSprayPattern attack pattern
#pragma once

#include "IAttackPattern.h"
#include <SFML/System/Vector2.hpp> 

// Forward declarations
class Player;
class IAddProjectile;

/// @brief An attack pattern consisting of a series of 6 bigger falling projectiles.
///
/// These projectiles are shot in an upwards spray with an 18-degree rotation
/// between each shot in the series. The pattern sets `switch_signal_` to true
/// when all projectiles in a series have been shot, indicating completion.
class UpwardSprayPattern : protected virtual IAttackPattern {
protected:
    /// @brief The time (in frames) required to reload before starting a new series of shots.
    int reload_time_ = 60;

    /// @brief Counter for the remaining time until the next series can start.
    int until_reload = reload_time_;

    /// @brief The delay (in frames) between individual projectile shots within a series.
    /// In this pattern, it's set to 0, meaning shots are fired consecutively without delay.
    const int projectile_delay = 0;

    /// @brief Counter for the remaining delay until the next projectile in the current series can be shot.
    int delay_left = projectile_delay;

    /// @brief The total number of projectiles to be shot in one series.
    const int shots_in_series = 6;

    /// @brief Counter for the number of shots remaining in the current series.
    int shots_left_ = 0;

    /// @brief The base scaling factor applied to the projectiles created by this pattern.
    const float projectile_scale_ = 0.5f;

    /// @brief An additional scaling factor applied to the projectiles.
    /// This might be intended for further size adjustments.
    const float scale = 1.f;

    /// @brief The velocity (speed) of the projectiles created by this pattern.
    const float velocity = 8.f;

    /// @brief The current direction vector for the projectiles in the spray.
    /// This vector is rotated for each subsequent projectile in a series.
    sf::Vector2f direction_;

    /// @brief A signal flag indicating that the current series of shots has completed.
    /// This can be used by an external manager to switch to a different attack pattern.
    bool switch_signal_ = false;

    /// @brief Implements the attack logic for this pattern.
    ///
    /// This method is called each frame to manage the shooting sequence,
    /// including delays between shots, reloads between series, and rotating
    /// the projectile direction for the spray effect.
    /// @param player - a reference to the Player object (though not directly used for target in this pattern's `attack` method).
    /// @param projectiles - a reference to an IAddProjectile interface to create new enemy projectiles.
    void attack(Player& player, IAddProjectile& projectiles) override;

    /// @brief Sets the reload time for the attack pattern.
    /// @param frames The new reload time in frames.
    void setReloadTime(int frames);
};
