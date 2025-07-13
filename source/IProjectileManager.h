/// @file IProjectileManager.h
/// @brief declares an interface of the ProjectileManager class
#pragma once
#include <memory>

namespace sf {
	class RenderWindow;
}
// forward declaration
class Projectile;
class IEnemyManager;
class IPlayer;
class IPickupManager;

/// @brief Interface of ProjectileManager manager class. 
class IProjectileManager {
public:
	/// @brief Pure virtual method. Used to pass the ownership of player-made Projectile objects to EventManager.
	/// @param proj - an r-value reference to the Projectile object.
	virtual void addPlayerProjectile(std::unique_ptr<Projectile>&& proj) = 0;
	/// @brief Pure virtual method. Used to pass the ownership of enemy-made Projectile objects to EventManager.
	/// @param proj - an r-value reference to the Projectile object.
	virtual void addEnemyProjectile(std::unique_ptr<Projectile>&& proj) = 0;
	/// @brief Render all the projectiles.
	/// @param window - a referencee to the sfml RenderWindow for rendering
	virtual void render(sf::RenderWindow& window) = 0;
	/// @brief Process the projectile manager. 
	/// Should be called every frame.
	/// @param enemy_manager - enemy manager for handling collisions.
	/// @param player - player for handling collisions.
	/// @param pickup_manager - pickup manager for creating pickups.
	virtual void process(IEnemyManager& enemy_manager, IPlayer& player, IPickupManager& pickup_manager) = 0;
	/// @brief Clears projectiles (both enemy and player) from the manager.
	/// This is typically used for game resets or bomb effects.
	virtual void clear() = 0;

};