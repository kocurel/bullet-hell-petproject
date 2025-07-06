/// @file TextureManager.h
/// @brief declares the TextureManager singleton class for game texture management.

#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>

/// @brief Manages the eager loading and retrieval of game texures.
/// TextureManager is designed as a Singleton to ensure only one
/// instance of it exists globally.
/// @warning If a requested texture is not found the TextureManager
/// returns a reference to the error texture accessable by getErrorTexture().
class TextureManager {
public:
    /// @brief Singleton instance.
    /// @return Returns the single instance of the RandomNumberGenerator
    static TextureManager& getInstance();

    /// @brief Returns a reference to a preloaded texture given its path.
    /// @details Returns an error texture if the texture wasn't preloaded.
    /// @param path Path to the preloaded texture.
    /// @return A const reference to the preloaded SFML Texture.
    /// @sa TextureManager::getErrorTexture
    const sf::Texture& getTexture(const std::string& path);

    /// @brief Preloads all the textures from paths passed by parameter.
    /// @details Loads the errorTexture if the texture can't be loaded.
    /// @param texturePaths A vector of strings, where each string is
    /// a path to a texture file.
    void loadAllTextures(const std::vector<std::string>& texturePaths);

    /// @brief The error texture.
    /// @return A const reference to the error texture.
    const sf::Texture& getErrorTexture();

    /// @brief Prevents copying of the Singleton instance. 
    TextureManager(const TextureManager&) = delete;

    /// @brief Prevents assignment of the Singleton instance. 
    TextureManager& operator=(const TextureManager&) = delete;
private:
    /// @brief Private Singleton Constructor.
    TextureManager();

    /// @brief A map containing the loaded textures.
    /// @details Paths to the textures are used as keys.
    std::map<std::string, sf::Texture> textures_;

    /// @brief The error texture.
    sf::Texture errorTexture_;
};