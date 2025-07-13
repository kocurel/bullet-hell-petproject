/// @file ProjectileStraight.h
/// @brief declares the ProjectileStraight subclass of Projectile
#pragma once
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
    explicit ProjectileStraight(IProjectileManager& projectiles, sf::Vector2f pos, sf::Vector2f dir,
        float velocity, float scaling, sf::Color color);
    /// @brief Handles the projectile's movement.
    void process();
};