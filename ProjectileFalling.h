/// @file ProjectileFalling.h
/// @brief declares the ProjectileFalling subclass of Projectile
#pragma once
#include "Projectile.h"

// forward declaration
namespace sf {
    class Texture;
}

/// Projectile type that has a downwards acceleration up to it's velocity value
class ProjectileFalling : public Projectile {
public:
    /// @brief Class constructor.
    /// @param projectiles - a reference to an IAddProjectile interface.
    /// @param scaling - factor scale of the projectile.
    explicit ProjectileFalling(IAddProjectile& projectiles, const float scaling);
    /// @brief Handles the projectile's movement.
    void process();
};