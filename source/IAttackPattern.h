/// @file IAttackPattern.h
/// @brief declares an interface of all attack pattern classes.
#pragma once
#include "Positionable.h"

// forward declarations
class IPlayer;
class IProjectileManager;

/// @brief Interface base class of all attack patterns
class IAttackPattern : public virtual Positionable {
protected:
	/// @brief Pure virtual function defining the logic of each attack pattern.
	/// @param player - a reference to the Player object.
	/// @param projectile_manager - a reference to the interface of ProjectileManager
	virtual void attack(IPlayer& player, IProjectileManager& projectile_manager) = 0;
};
