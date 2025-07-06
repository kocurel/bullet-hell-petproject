#include "TextureManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>

TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

TextureManager::TextureManager() {
    if (!errorTexture_.loadFromFile("assets/error.png")) {
        std::cerr << "WARNING: Could not load default error texture 'assets/error.png'\n";
        sf::Image errorImage({ 64, 64 }, sf::Color::Magenta);
        if (!errorTexture_.loadFromImage(errorImage)) {
            std::cerr << "ERROR: Could not create a placeholder error texture\n";
        }
    }
}

const sf::Texture& TextureManager::getTexture(const std::string& filename) {
    auto it = textures_.find(filename);
    if (it != textures_.end()) {
        return it->second;
    }
    std::cerr << "ERROR: Texture '" << filename << "' was requested but not pre-loaded!\n";
    return getErrorTexture();
}

void TextureManager::loadAllTextures(const std::vector<std::string>& texturePaths) {
    std::cout << "Starting texture loading...\n";
    for (const auto& path : texturePaths) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "ERROR: Failed to load texture: " << path << "\n";
            textures_.emplace(path, getErrorTexture());
        }
        else {
            textures_.emplace(path, std::move(texture));
            std::cout << "Loaded: " << path << "\n";
        }
    }
    std::cout << "Finished texture loading.\n\n";
}

const sf::Texture& TextureManager::getErrorTexture() {
    return errorTexture_;
}