/// @file PickupManager.h
/// @brief declares the PickupManager class
#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ranges>
#include <mutex>
#include "Pickup.h"

// Forward declarations
class Pickup;
class Player;

/// @brief Manages the lifecycle, processing, and rendering of various in-game pickups.
///
/// This class is responsible for creating new pickups, updating their state,
/// rendering them on the screen, and cleaning up disabled pickups. It uses
/// `std::unique_ptr` for automatic memory management of pickups and a mutex
/// for thread-safe operations, particularly during pickup creation.
class PickupManager {
private:
	/// @brief A vector holding unique pointers to all active pickups.
	std::vector<std::unique_ptr<Pickup>> pickups_;

	/// @brief Counter used to control the frequency of the cleanup operation.
	/// The cleanup function runs only when this counter reaches zero.
	/// @sa cleanup()
	int cleanup_counter_ = 0;
	
	/// @brief Mutex to protect access to the `pickups_` vector, especially during addition.
	/// This ensures thread safety when `createPickup` is called from multiple threads.
	/// This is neccessary because Player and EnemyManager run in parallel, and the Player needs 
	/// safe access to iterate through all the pickups for collision checking, 
	/// while the Enemies create new Pickups on destruction/
	std::mutex mtx_;
	
	/// @brief Cleans up disabled pickups from the pickups_ vector.
	///
	/// This method is called periodically based on cleanup_counter_.
	/// It removes any Pickup objects that have been marked as disabled.
	void cleanup();
public:
	/// @brief Clears all pickups from the manager.
	void clearPickups();

	/// @brief Gets a constant reference to the vector of pickups
	/// @return A const reference to the pickups_ vector, allowing read-only access.
	const std::vector<std::unique_ptr<Pickup>>& getPickups();

	/// @brief Processes all active pickups.
	///
	/// This method first calls cleanup() to remove disabled pickups.
	/// Then, it iterates through all remaining active pickups and calls their process() method.
	void process();
	/// @brief Renders all active pickups on the provided SFML render window.
	///
	/// This method iterates through all active pickups and calls their render() method.
	/// @param window - a reference to the SFML RenderWindow where pickups will be drawn
	void renderPickups(sf::RenderWindow& window);
	/// @brief Gets a reference to the internal mutex.
	///
	/// This allows external code to lock the mutex when performing operations
	/// that might conflict with createPickup like the Player object 
	/// iterating through the vector in another thread
	std::mutex& getMutex();

	/// @brief Creates a new pickup of a specified type at a given position.
	///
	/// This method uses a `std::lock_guard` to ensure thread-safe addition of new pickups
	/// to the `pickups_` vector. It uses a switch statement to create different
	/// types of pickups based on the provided `type` integer.
	/// @param type - an integer representing the type of pickup to create (0: Health, 1: AttackUp, etc.).
	/// @param posistion - The SFML 2D vector representing the initial position of the pickup.
	void createPickup(int type, sf::Vector2f posistion);

	/// @brief Default destructor
	~PickupManager();
};