/// @file ProjectileManager.h
/// @brief declares the ProjectileManager class
#pragma once

#include "IProjectileManager.h"
#include <vector> 
#include <memory>
#include <functional>

// Forward declaration
class Projectile;

namespace sf {
    class RenderWindow;
}

/// @brief Manages collections of player and enemy projectiles.
///
/// This class is responsible for owning, processing, rendering, and cleaning up
/// both player-fired and enemy-fired projectiles.
class ProjectileManager : public IProjectileManager {
private:
    /// @brief A vector holding unique pointers to all active enemy projectiles.
    std::vector<std::unique_ptr<Projectile>> enemy_projectiles_;

    /// @brief A vector holding unique pointers to all active player projectiles.
    std::vector<std::unique_ptr<Projectile>> player_projectiles_;

    /// @brief Counter used to control the frequency of the projectile cleanup operation.
    /// Cleanup runs only when this counter reaches zero.
    int cleanup_counter_ = 120;

    /// @brief A function object (lambda) to check if a projectile is NOT disabled.
    /// Used with C++20 ranges for filtering active projectiles.
    std::function<bool(const std::unique_ptr<Projectile>&)> is_not_disabled;

    /// @brief A function object (lambda) to check if a projectile IS disabled.
    /// Used with `std::remove_if` during cleanup.
    std::function<bool(const std::unique_ptr<Projectile>&)> is_disabled;

    /// @brief Cleans up disabled projectiles from both enemy and player projectile collections.
    ///
    /// This method is called periodically based on `cleanup_counter_`.
    /// It removes any `Projectile` objects that have been marked as disabled (`isDisabled()`).
    void cleanupProjectiles();

public:
    /// @brief Constructor for the ProjectileManager.
    /// Initializes the `is_not_disabled` and `is_disabled` function objects.
    ProjectileManager();

    /// @brief Clears all projectiles (both enemy and player) from the manager.
    /// This is typically used for game resets or bomb effects.
    void clear() override;

    /// @brief Processes all active projectiles.
    ///
    /// This method first calls `cleanupProjectiles()` to remove disabled ones.
    /// Then, it iterates through all remaining active enemy and player projectiles
    /// and calls their `process()` method.
    void process(IEnemyManager& enemy_manager, Player& player, IPickupManager& pickup_manager) override;

    /// @brief Creates and adds a new player-fired projectile to the manager.
    /// This method overrides the pure virtual function from `IAddProjectile`.
    /// @param projectile - An rvalue reference to a unique_ptr holding the new projectile.
    void createPlayerProjectile(std::unique_ptr<Projectile>&& projectile) override;

    /// @brief Creates and adds a new enemy-fired projectile to the manager.
    /// This method overrides the pure virtual function from `IAddProjectile`.
    /// @param projectile - An rvalue reference to a unique_ptr holding the new projectile.
    void createEnemyProjectile(std::unique_ptr<Projectile>&& projectile) override;

    /// @brief Renders all active projectiles (both player and enemy) on the provided SFML render window.
    /// @param window - A reference to the SFML RenderWindow where projectiles will be drawn.
    void render(sf::RenderWindow& window) override;

    /// @brief Gets a constant reference to the vector of player projectiles.
    /// @return A const reference to player_projectiles_.
    const std::vector <std::unique_ptr<Projectile>>& getPlayerProjectiles();

    /// @brief Gets a constant reference to the vector of enemy projectiles.
    /// @return A const reference to enemy_projectiles_.
    const std::vector <std::unique_ptr<Projectile>>& getEnemyProjectiles();
};
