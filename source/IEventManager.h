/// @file IEventManager.h
/// @brief declares the interface of the EventManager
#pragma once
#include <memory>
class Event;

/// @brief Interface of the EventManager.
class IEventManager {
public:
	/// @brief Used to set the waiting_ flag to false.
	/// This interface is used by the EnemyManager to let 
	/// the EventManager know that there aren't any enemies left.
	virtual void addEvent(std::unique_ptr<Event>&& event) = 0;
	virtual void endWave() = 0;
};