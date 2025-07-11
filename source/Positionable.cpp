#include "Positionable.h"

sf::Vector2f Positionable::getPosition() {
    return position_;
}

void Positionable::setPosition(sf::Vector2f pos) {
    position_ = pos;
}