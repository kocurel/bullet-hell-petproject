/// @file UserInterface.h
/// @brief declares UserInterface singleton class
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/// @brief Manages and renders all user interface (UI) elements for the game.
///
/// This class implements the Singleton design pattern to ensure a single instance
/// manages all UI components such as score, player life, bombs, and various
/// game state overlays (game over, stage over, selection screen).
class UserInterface {
private:
    /// @brief The current score of the player.
    int score_value_ = 0;

    /// @brief SFML sprite for displaying player's life (heart icon).
    sf::Sprite heart_;

    /// @brief SFML sprite for displaying player's bombs (bomb icon).
    sf::Sprite bomb_;

    /// @brief Current number of player's lives.
    int life_ = 3;

    /// @brief Current number of player's bombs.
    int bombs_ = 3;

    /// @brief SFML text object for displaying the score.
    sf::Text score_text_;

    /// @brief SFML text object for displaying selection screen messages.
    sf::Text selection_text_;

    /// @brief SFML text object for displaying "GAME OVER" message.
    sf::Text game_over_text_;

    /// @brief SFML text object for displaying "STAGE OVER" message.
    sf::Text stage_over_text_;

    /// @brief SFML text object for displaying the final score on game over/stage over screens.
    sf::Text game_over_score_text_;

    /// @brief SFML font object used for all text elements.
    sf::Font font_;

    /// @brief SFML RectangleShape representing the main game play area.
    sf::RectangleShape game_space_;

    /// @brief SFML RectangleShape for the top black bar of the UI.
    sf::RectangleShape black_bar1_;

    /// @brief SFML RectangleShape for the left black bar of the UI.
    sf::RectangleShape black_bar2_;

    /// @brief SFML RectangleShape for the bottom black bar of the UI.
    sf::RectangleShape black_bar3_;

    /// @brief SFML RectangleShape for the right black bar of the UI.
    sf::RectangleShape black_bar4_;

    /// @brief SFML RectangleShape used as a semi-transparent overlay for pause/game over screens.
    sf::RectangleShape shadow_overlay_;

    /// @brief Private constructor to enforce the Singleton pattern.
    /// Initializes all UI elements, their positions, sizes, and textures/fonts.
    UserInterface();

public:
    /// @brief Gets the single instance of the UserInterface.
    /// @return A reference to the UserInterface instance.
    static UserInterface& getInstance();

    /// @brief Deleted copy constructor to prevent copying.
    UserInterface(const UserInterface&) = delete;
    /// @brief Deleted copy assignment operator to prevent copying.
    UserInterface& operator=(const UserInterface&) = delete;

    /// @brief Updates the displayed number of bombs.
    /// @param bomb The new integer value for bombs.
    void updateBombs(int bomb);

    /// @brief Updates the displayed number of player lives.
    /// @param life The new integer value for lives.
    void updateLife(int life);

    /// @brief Increases the player's score by a given value.
    /// Updates the score text display.
    /// @param value The integer amount to add to the score.
    void increaseScore(int value);

    /// @brief Resets the player's score to zero.
    /// Updates the score text display.
    void resetScore();

    /// @brief Gets the current score value.
    /// @return An integer representing the current score.
    int getScore();

    /// @brief Renders the "GAME OVER" screen overlay.
    /// @param window A reference to the SFML RenderWindow to draw on.
    void renderGameOver(sf::RenderWindow& window);

    /// @brief Renders the "STAGE OVER" screen overlay.
    /// @param window A reference to the SFML RenderWindow to draw on.
    void renderStageOver(sf::RenderWindow& window);

    /// @brief Renders the stage selection screen overlay.
    /// @param window A reference to the SFML RenderWindow to draw on.
    void renderSelection(sf::RenderWindow& window);

    /// @brief Renders the background for the main game space.
    /// @param window A reference to the SFML RenderWindow to draw on.
    void renderBottom(sf::RenderWindow& window);

    /// @brief Renders the top UI elements, including score, lives, and bombs.
    /// @param window A reference to the SFML RenderWindow to draw on.
    void renderTop(sf::RenderWindow& window);
};
