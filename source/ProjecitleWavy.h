#pragma once
/// @file ProjecitleWavy.h
/// @brief declares the ProjecitleWavy subclass of Projectile
#include "Projectile.h"

namespace sf {
    class Texture;
}
/// Projectile type that moves in a straight line
class ProjecitleWavy : public Projectile {
public:
    /// @brief Class constructor.
    /// @param projectiles - a reference to an IAddProjectile interface.
    /// @param scaling - factor scale of the projectile.
    explicit ProjecitleWavy(IProjectileManager& projectiles, const float scaling);
    /// @brief Handles the projectile's movement.
    void process();
};