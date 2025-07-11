#include "SpriteOwner.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

SpriteOwner::SpriteOwner() : sprite_(TextureManager::getInstance().getErrorTexture()) {}

bool SpriteOwner::isDisabled() const {
    return disabled_;
}

void SpriteOwner::disable() {
    disabled_ = true;
}

void SpriteOwner::render(sf::RenderWindow& window) const {
    window.draw(sprite_);
}