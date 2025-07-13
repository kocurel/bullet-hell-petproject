/// @file SeriesInLinePattern.h
/// @brief declares SeriesInLinePattern attack pattern
#pragma once
#include "IAttackPattern.h"
#include <concepts>
#include "ProjectileBuilder.h"
#include "ProjectileFalling.h"
#include "IProjectileManager.h"
#include "IPlayer.h"
#include "Projectile.h"

class IPlayer;
class IAddProjectile;
/// @brief An attack pattern where a series of small projectiles are shot in a line.
///
/// This pattern involves shooting a fixed number of projectiles (`shots_in_series`)
/// with a small `projectile_delay` between each shot. After the series is complete,
/// there's a longer `reload_time_` before the next series can begin.
/// It signals completion of a series via `switch_signal_`.
template<Derived<Projectile> T>
class SeriesInLinePattern : protected virtual IAttackPattern {
protected:
    /// @brief The time (in frames) required to reload before starting a new series of shots.
    const int reload_time_ = 60;

    /// @brief Counter for the remaining time until the next series can start.
    int until_reload = reload_time_;

    /// @brief The delay (in frames) between individual projectile shots within a series.
    const int projectile_delay = 4;

    /// @brief Counter for the remaining delay until the next projectile in the current series can be shot.
    int delay_left = projectile_delay;

    /// @brief The total number of projectiles to be shot in one series.
    const int shots_in_series = 8;

    /// @brief Counter for the number of shots remaining in the current series.
    int shots_left_ = 0;

    /// @brief The scaling factor applied to the projectiles created by this pattern.
    const float projectile_scale_ = 0.5f;

    /// @brief A signal flag indicating that the current series of shots has completed.
    /// This can be used by an external manager to switch to a different attack pattern.
    bool switch_signal_ = false;

    /// @brief Implements the attack logic for this pattern.
    ///
    /// This method is called each frame to manage the shooting sequence,
    /// including delays between shots and reloads between series.
    /// @param player - a reference to the Player object, used to determine target position.
    /// @param projectiles - a reference to an IAddProjectile interface to create new enemy projectiles.
    void attack(IPlayer& player, IProjectileManager& projectiles) override {
        static ProjectileBuilder<T> pbs(projectiles);
        if (shots_left_ > 0) {
            if (--delay_left <= 0) {
                if (--shots_left_ == 0) {
                    switch_signal_ = true;
                }
                delay_left = projectile_delay;
                std::unique_ptr<Projectile> projectile =
                    pbs.direction(player.getPosition() - position_)
                    .position(position_)
                    .scale(projectile_scale_)
                    .velocity(8.f)
                    .build();
                projectiles.addEnemyProjectile(std::move(projectile));
            }
        }
        else if (--until_reload <= 0) {
            switch_signal_ = false;
            until_reload = reload_time_;
            shots_left_ = shots_in_series;
        }
    }
};
