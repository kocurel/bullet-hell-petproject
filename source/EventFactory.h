/// @file EventFactory.h
/// @brief declares EventFactory class used to create various events.
#pragma once
#include <memory>
#include "Event.h"

// forward declarations
class IProjectileManager;
class IEventManager;
class ProjectileManager;
class Enemy;

/// @brief Factory class responsible for creating different types of game events.
/// This class encapsulates the creation logic for various events, such as spawning enemies or projectiles,
/// and passes them to the event manager.
class EventFactory {
private:
    /// @brief Reference to the event manager interface, used to add newly created events.
    IEventManager& event_manager_;
    /// @brief Reference to the projectile addition interface, used by events that spawn projectiles.
    IProjectileManager& projectile_manager_;
public:
    /// @brief Constructs an EventFactory.
    /// @param projectiles - a reference to the IProjectileManager interface of the ProjectileManager manager.
    /// @param event_queue - a reference to the IAddEvent interface of the EventManager.
    EventFactory(IProjectileManager& projectiles, IEventManager& event_queue);

    /// @brief Creates and configures a game event based on its ID.
    /// This method uses a switch statement to determine which type of event to create (e.g., new enemy, new projectile).
    /// The created event is then configured with countdown and wait settings and passed to the event manager.
    /// @param id - hexadecimal identifier specifying the type of event to create.
    /// @param wait - flag indicating whether the event should trigger a waiting_ flag of EventManager.
    /// @param countdown - the number of frames until the event is ready to trigger.
    void createEvent(int id, bool wait, int countdown);
};