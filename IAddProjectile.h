/// @file IAddProjectile.h
/// @brief declares an interface of the ProjectileManager class
#pragma once
#include <memory>

// forward declaration
class Projectile;

/// @brief Interface of ProjectileManager manager class. 
/// Used to pass ownership of Projectile objects into the projectile manager
class IAddProjectile {
public:
	/// @brief Pure virtual method. Used to pass the ownership of player-made Projectile objects to EventManager.
	/// @param proj - an r-value reference to the Projectile object.
	virtual void createPlayerProjectile(std::unique_ptr<Projectile>&& proj) = 0;
	/// @brief Pure virtual method. Used to pass the ownership of enemy-made Projectile objects to EventManager.
	/// @param proj - an r-value reference to the Projectile object.
	virtual void createEnemyProjectile(std::unique_ptr<Projectile>&& proj) = 0;
};