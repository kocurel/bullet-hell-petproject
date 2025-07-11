#pragma once
#include <memory>
#include <vector>

namespace sf {
	class RenderWindow;
}

class Enemy;
class Player;
class IProjectileManager;
class IPickupManager;

/// @brief Interface of the EnemyManager class, handles processing, taking ownership and rendering enemies
class IEnemyManager {
public:
	/// @brief Main process method, should be called each frame.
	/// @param player - reference to the player for directed attacking.
	/// @param projectiles - reference to the projectile manager for creating new projectiles.
	/// @param pickups - reference to the pickups manager for creating new pickups.
	virtual void process(Player& player, IProjectileManager& projectiles, IPickupManager& pickups) = 0;
	/// @brief Creates a new enemy by taking ownership of the Enemy object passed by parameter.
	/// @param enemy - rvalue reference of the unique_pointer to Enemy object.
	virtual void createEnemy(std::unique_ptr<Enemy>&& enemy) = 0;
	/// @brief Renders all enemies on the render window.
	/// @param window - reference to the SFML RenderWindow.
	virtual void render(sf::RenderWindow& window) const = 0;
	/// @brief Remove the stored enemy objects from memory
	virtual void clear() = 0;
	virtual const std::vector<std::unique_ptr<Enemy>>& getEnemies() const = 0;

};