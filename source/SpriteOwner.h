/// @file SpriteOwner.h
/// @brief declares the SpriteOwner base class
#pragma once
#include "SFML/Graphics.hpp"
#include <functional>

/// @brief Base class for objects that own and manage an SFML sprite.
/// Provides basic functionalities for rendering a sprite, and disabling the object.
class SpriteOwner {
protected:
    /// @brief Flag indicating if the sprite owner is disabled (for rendering and processing).
    bool disabled_ = false;
    
    /// @brief The SFML sprite object owned by this instance.
    sf::Sprite sprite_;

    /// @brief Protected default constructor.
    /// Initializes the internal sf::Sprite with an error texture.
    /// This constructor is protected to ensure creation through derived classes.
    SpriteOwner();
public:
    /// @brief Checks if the sprite owner is currently disabled.
    /// @return True if the object is disabled, false otherwise.
    bool isDisabled() const;
    
    /// @brief Disables the sprite owner.
    /// Sets the internal flag to true, preventing further rendering or processing.
    void disable();

    /// @brief Renders the owned sprite to the specified SFML render window.
    /// @param window The SFML RenderWindow to which the sprite will be drawn.
    void render(sf::RenderWindow& window) const;
};