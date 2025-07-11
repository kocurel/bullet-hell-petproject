/// @file InputManager.h
/// @brief class responsible for storing information about keyboard inputs
#pragma once 

#include <SFML/Window/Keyboard.hpp> 
#include <map>

/// @brief The InputManager class handles keyboard input states.
///
/// This class implements the Singleton design pattern to ensure that there is
/// only one instance of the input manager throughout the application.
/// It tracks which keys were just pressed in the current frame
class InputManager {
public:
    /// @brief Get the single instance of the InputManager.
    /// @return A reference to the InputManager instance.
    static InputManager& getInstance();

    /// Deleted copy constructor to prevent copying
    InputManager(const InputManager&) = delete;
    /// Deleted assignment operator to prevent copying
    InputManager& operator=(const InputManager&) = delete;

    /// @brief Sets the state of a key to 'just pressed'.
    /// 
    /// This method should be called when an sf::Event::KeyPressed event is detected.
    /// The key's 'just pressed' state will be true until clearInputs() is called.
    /// 
    /// @param key The SFML keyboard key code (e.g., sf::Keyboard::Z, sf::Keyboard::Space).
    void setKeyJustPressed(sf::Keyboard::Key key);

    /// @brief Checks if a key was just pressed in the current frame.
    /// 
    /// A key is considered 'just pressed' if it transitioned from not pressed
    /// to pressed within the current frame. This state is reset by clearInputs()
    /// at the end of each frame.
    /// 
    /// @param key The SFML keyboard key code to check.
    /// @return True if the key was just pressed, false otherwise.
    bool isKeyJustPressed(sf::Keyboard::Key key) const;

    /// @brief Clears all 'just pressed' states for all keys.
    /// 
    /// This method should be called once at the end of each game loop iteration
    /// (after all events have been processed and input queries have been made)
    /// to prepare for the next frame.
    void clearInputs();

private:
    /// @brief Private constructor to enforce Singleton pattern.
    InputManager();

    /// Map to store the 'just pressed' state for each key.
    /// A key is true if it was pressed in the current frame, false otherwise.
    std::map<sf::Keyboard::Key, bool> is_key_just_pressed_;
};
