/// @file PickupManager.h
/// @brief declares the PickupManager class
#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ranges>
#include "Pickup.h"
#include "IPickupManager.h"

// Forward declarations
class Pickup;
class Player;

/// @brief Manages the lifecycle, processing, and rendering of various in-game pickups.
///
/// This class is responsible for creating new pickups, updating their state,
/// rendering them on the screen, and cleaning up disabled pickups. It uses
/// `std::unique_ptr` for automatic memory management of pickups.
class PickupManager : public IPickupManager {
private:
	/// @brief A vector holding unique pointers to all active pickups.
	std::vector<std::unique_ptr<Pickup>> pickups_;

	/// @brief Counter used to control the frequency of the cleanup operation.
	/// The cleanup function runs only when this counter reaches zero.
	/// @sa cleanup()
	int cleanup_counter_ = 0;

	/// @brief Cleans up disabled pickups from the pickups_ vector.
	///
	/// This method is called periodically based on cleanup_counter_.
	/// It removes any Pickup objects that have been marked as disabled.
	void cleanup();
public:
	/// @brief Clears all pickups from the manager.
	void clear() override;

	/// @brief Processes all active pickups.
	///
	/// This method first calls cleanup() to remove disabled pickups.
	/// Then, it iterates through all remaining active pickups and calls their process() method.
	void process() override;

	/// @brief Renders all active pickups on the provided SFML render window.
	///
	/// This method iterates through all active pickups and calls their render() method.
	/// @param window - a reference to the SFML RenderWindow where pickups will be drawn
	void render(sf::RenderWindow& window) override;

	/// @brief Creates a pickup by taking ownership of the Pickup passed by parameter.
	/// @param pickup - rvalue reference to a unique_pointer to a Pickup object.
	void createPickup(std::unique_ptr<Pickup>&& pickup) override;

	/// @brief Default destructor
	~PickupManager();
};