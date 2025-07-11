#pragma once
#include <memory>
#include "Pickup.h"
namespace sf {
	class RenderWindow;
}
class Player;

class IPickupManager {
public:
	/// @brief Clears all pickups from the manager.
	virtual void clear() = 0;
	/// @brief Renders all the pickups to the render window.
	/// @param window - a reference to the SFML RenderWindow.
	virtual void render(sf::RenderWindow& window) = 0;
	/// @brief Processes all active pickups.
	virtual void process() = 0;
	/// @brief Creates a pickup by taking ownership of the Pickup passed by parameter.
	/// @param pickup - rvalue reference to a unique_pointer to a Pickup object.
	virtual void createPickup(std::unique_ptr<Pickup>&& pickup) = 0;
};