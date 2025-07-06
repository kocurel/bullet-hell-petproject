/// @file INotifyEndWave.h
/// @brief declares an interface of the EventManager
#pragma once

/// @brief Interface of the EventManager.
class INotifyEndWave {
public:
	/// @brief Used to set the waiting_ flag to false.
	/// This interface is used by the EnemyManager to let 
	/// the EventManager know that there aren't any enemies left.
	virtual void endWave() = 0;
};