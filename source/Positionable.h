/// @file Positionable.h
/// @brief declares the Positionable class for objects that have a 2D position
#pragma once

#include <SFML/System/Vector2.hpp>

/// @brief Provides basic position management for objects in a 2D space.
///
/// This class defines a common interface for objects that have a position
/// represented by an SFML 2D vector, allowing them to get and set their coordinates.
class Positionable {
protected:
    /// @brief The 2D position of the object in game coordinates.
    sf::Vector2f position_;

public:
    /// @brief Gets the current position of the object.
    /// @return An sf::Vector2f representing the object's current position.
    sf::Vector2f getPosition();

    /// @brief Sets the position of the object.
    /// @param pos The new sf::Vector2f position for the object.
    void setPosition(sf::Vector2f pos);
};
