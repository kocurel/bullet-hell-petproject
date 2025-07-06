/// @file NewEnemy.h
/// @brief declares the NewEnemy Event subclass that creates a new Enemy
#pragma once
#include "Event.h"
#include <memory>

class Enemy;
class EnemyManager;
class ProjectileManager;

/// @brief An event that triggers the creation of a new enemy in the game.
/// This class inherits from Event and encapsulates a unique_ptr to an Enemy object,
/// which is then moved into the EnemyManager manager upon release.
class NewEnemy : public Event {
private:
    /// @brief The unique pointer to the Enemy object to be created when this event is released.
    std::unique_ptr<Enemy> _enemy;
public:
    /// @brief Constructs a NewEnemy event by taking ownership of an Enemy object.
    /// @param enemy An rvalue reference to a unique_ptr<Enemy>. Ownership is moved from this parameter.
    explicit NewEnemy(std::unique_ptr<Enemy>&& enemy);

    /// @brief Implements the action to be performed when the event is released.
    /// This method moves the encapsulated Enemy object into the EnemyManager manager, effectively spawning it.
    /// @param enemies - a reference to the EnemyManager manager, used to add the new enemy.
    /// @param projectiles - a reference to the ProjectileManager manager (not used by this specific event, but required by base class signature).
    void onRelease(EnemyManager& enemies, ProjectileManager& projectiles) override;
};