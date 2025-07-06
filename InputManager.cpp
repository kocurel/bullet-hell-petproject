// InputManager.cpp
#include "InputManager.h"
#include <iostream>

InputManager& InputManager::getInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager() {}

void InputManager::setKeyJustPressed(sf::Keyboard::Key key) {
    is_key_just_pressed_[key] = true;
}

bool InputManager::isKeyJustPressed(sf::Keyboard::Key key) const {
    auto it = is_key_just_pressed_.find(key);
    if (it != is_key_just_pressed_.end()) {
        return it->second;
    }
    return false;
}

void InputManager::clearInputs() {
    for (auto& pair : is_key_just_pressed_) {
        pair.second = false;
    }
}
