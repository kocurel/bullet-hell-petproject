/// @file Event.h
/// @brief declares the abstract base class of all Event types
#pragma once
//forward declarations
class EnemyManager;
class ProjectileManager;

/// @brief Represents a game event that can be triggered after a countdown.
/// This is an abstract base class, requiring derived classes to implement the 'onRelease' behavior.
class Event {
private:
    /// @brief Internal counter for frames until the event is ready to trigger
    int frames_countdown_ = 0;
    
    /// @brief Flag indicating if the event enables the EventManager::waiting_ flag, marking an and of a wave.
    bool wait_ = false;
public:
    /// @brief Gets the value of the wait_ flag of the event.
    /// @return The value of wait_ flag.
    /// @sa wait_
    bool get_wait() const;
    
    /// @brief Sets the value of the wait_ flag of the event.
    /// @param wait - the new value of the wait_ flag.
    /// @sa wait_
    void setWait(bool wait);
    
    /// @brief Sets the initial countdown duration for the event.
    /// @param frames The number of frames to count down before the event is ready.
    void setCountdown(int frames);
    
    /// @brief Decrements the event's internal frame countdown.
    /// @return True if the countdown has reached zero or less, 
    /// indicating the event is ready to trigger; false otherwise.
    bool countdown();
    
    /// @brief Pure virtual function to define the action performed when the event is released.
    /// Derived classes must implement this to define specific event behaviors.
    /// @param enemies - A reference to the EnemyManager manager, allowing event to interact with enemies.
    /// @param projectiles - A reference to the ProjectileManager manager, allowing event to interact with projectiles.
    virtual void onRelease(EnemyManager& enemies, ProjectileManager& projectiles) = 0;

    /// @brief Virtual destructor to ensure proper cleanup of derived Event objects.
    virtual ~Event() = default;
};