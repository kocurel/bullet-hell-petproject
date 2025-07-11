/// @file Pickup.h
/// @brief declares the abstract base Pickup class, from which all Pickup subclasses inherit.
#pragma once
#include "Positionable.h"
#include "SpriteOwner.h"
#include "CollisionCircle.h"
#include <functional>
#include "TextureManager.h"

// forward declaration
class Player;

/// @brief Abstract base class for all pickup types.
class Pickup : public Positionable, public SpriteOwner {
protected:
	/// @brief hitbox of the pickup.
	CollisionCircle hitbox_;

	/// @brief Default Constructor. Initializes the sprite and the hitbox.
	Pickup();

	/// @brief Moves the pickup, its hitbox and sprite by a displacement.
	/// @param displacement - the displacement vector. 
	void move(sf::Vector2f displacement);
public:
	/// @brief getter of the hitbox_
	/// @return Returns a const reference to the CollisionCircle hitbox.
	const CollisionCircle& getHitbox() const;

	/// @brief Pure virtual function. To be called by the Player object when it detects the collision
	/// @param player - A reference to the Player object. 
	/// Neccessary for any given Pickup to be able to modify player stats.
	virtual void onPickup(Player& player) = 0;

	/// @brief Process function. Handles the movement of a Pickup object. 
	/// Should get called every frame.
	void process();

	/// @brief The default virtual destructor.
	virtual ~Pickup() = default;
};