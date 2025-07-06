/// @file NewProjectile.h
/// @brief declares the NewProjectile event type
#pragma once
#include "Event.h"
#include <memory>

class EnemyManager;
class Projecitles;
class Projectile;

/// @brief An event that triggers the creation of a new projectile in the game.
/// This class inherits from Event and encapsulates a unique_ptr to a Projectile object,
/// which is then added to the ProjectileManager manager upon release.
class NewProjectile : public Event {
private:
    /// @brief The unique pointer to the Projectile object to be created when this event is released.
    std::unique_ptr<Projectile> projectile_;
public:
    /// @brief Constructs a NewProjectile event by taking ownership of a Projectile object.
    /// @param projectile An rvalue reference to a unique_ptr<Projectile>. Ownership is moved from this parameter. 
    explicit NewProjectile(std::unique_ptr<Projectile>&& projectile);

    /// @brief Implements the action to be performed when the event is released.
    /// This method adds the encapsulated Projectile object to the ProjectileManager manager, effectively spawning it.
    /// @param enemies - a reference to the EnemyManager manager (not used by this specific event, but required by base class signature).
    /// @param projectiles - a reference to the ProjectileManager manager, used to add the new projectile.
    void onRelease(EnemyManager& enemies, ProjectileManager& projectiles) override;
};