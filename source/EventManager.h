/// @file EventManager.h
/// @brief declares the EventManager manager class responsible
/// for storing and management of Event class objects
#pragma once
#include <queue>
#include <memory>
#include "IEventManager.h"
#include "IAddEvent.h"

// forward declarations
class Event;
class EnemyManager;
class ProjectileManager;

/// @brief Event manager class.
/// Keeps all events inside a queue of unique pointers.
/// Responsible for counting down the frames and releasing events.
class EventManager : public IEventManager {
private:
    /// @brief Queue of Event objects.
    std::queue<std::unique_ptr<Event>> events_;
    /// @brief Flag, True if the previously released event had wait_ = true.
    bool waiting_ = false;

public:
    /// @brief Counts down frames for the top event of the queue.
    /// Calls onRelease when the event is ready
    /// @param enemies - a reference to the EnemyManager, to be passed to the Event on release
    /// @param projectiles - a reference to the ProjectileManager, to be passed to the Event on release
    void process(EnemyManager& enemies, ProjectileManager& projectiles);
    /// @brief The default constructor.
    EventManager();
    /// @brief Implementation of the IEventManager interface.
    /// Sets waiting_ to false, ending the enemy wave.
    void endWave() override;
    /// @brief Checks if the stage is over
    /// @return Returns true when there no events in the queue and waiting_ is set to false.
    bool isStageOver();
    /// @brief Clear the events_ Event queue.
    void clearEvents();
    /// @brief Adds an event to the events_ Event queue.
    /// @param event - a reference to the Event to be added.
    void addEvent(std::unique_ptr<Event>&& event) override;
};