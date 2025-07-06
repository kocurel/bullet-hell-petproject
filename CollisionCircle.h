/// @file CollisionCircle.h
/// @brief declares the CollisionCircle class for
/// collision detection.
#pragma once
#include <SFML/Graphics.hpp>
/// @brief A collision circle used for collision detection.
class CollisionCircle {
public:
    /// @brief The position of the center of the circle.
    sf::Vector2f position_;
    /// @brief The radius of the circle.
    float radius_;
    /// @brief The default constructor.
    /// The default values are position_(0, 0), radius_(0).
    CollisionCircle();
    /// @brief Checks if the CollisionCircle object is colliding with another CollisionCircle object.
    /// @details The two circle are colliding if they overlap ie. the distance between them is lower than sum of their radii.
    /// @param other - a const reference to the other CollisionCircle object.
    /// @return Returns true if the two circles are colliding, false otherwise.
    bool checkCollision(const CollisionCircle& other) const;
};