/// @file ProjectileStraight.h
/// @brief declares the ProjectileStraight subclass of Projectile#pragma once
#include "Projectile.h"

namespace sf {
    class Texture;
}
/// Projectile type that moves in a straight line
class ProjectileStraight : public Projectile {
public:
    /// @brief Class constructor.
    /// @param projectiles - a reference to an IAddProjectile interface.
    /// @param scaling - factor scale of the projectile.
    explicit ProjectileStraight(IAddProjectile& projectiles, const float scaling);
    /// @brief Handles the projectile's movement.
    void process();
};