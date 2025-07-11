/// @file IAddEvent.h
/// @brief declares an interface of EventManager class
#pragma once
#include <memory>

// forward declarations
class Event;

/// @brief Interface class of EventManager
class IAddEvent {
public:
	/// @brief Pure virtual method. Used to pass the ownership of Event objects to EventManager.
	/// @param event - and r-value reference to the Event object.
	virtual void addEvent(std::unique_ptr<Event>&& event) = 0;
};