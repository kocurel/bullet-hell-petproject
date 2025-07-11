/// @file Game.h
/// @brief declares the core game manager class
#pragma once
#include <vector>
#include <memory>
#include "ProjectileManager.h"
#include "EventManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "EventParser.h"
#include "PickupManager.h"

//forward declarations
namespace sf {
    class RenderWindow;
}
/// @brief Main class responsible for handling game logic.
/// Has to be called each frame with process() and render().
/// For the Game class to work a pointer to the SFML Window 
/// has to be set using the setRenderWindow(sf::RenderWindow*) method.
class Game {
private:
    /// @brief Level selection flag. True if the player is currently choosing the stage
    bool stage_selection = true;
    /// @brief game over flag. True when the player loses.
    bool game_over_ = false;
    /// @brief Stage finished flag. True when the player finishes a stage.
    bool stage_finished_ = false;
    /// @brief A pointer to the SFML RenderWindow.
    sf::RenderWindow* window_ = nullptr;
    /// @brief EventParser object. Used to read stage files.
    EventParser parser_;
    /// @brief Projectile mnager object.
    ProjectileManager projectiles_;
    /// @brief Event manager object.
    EventManager event_manager_;
    /// @brief Pickup manager object.
    PickupManager pickup_manager_;
    /// @brief Enemy manager object.
    EnemyManager enemy_manager_;
    /// @brief Player object
    Player player_;
     void checkLevelSelection();
     /// @brief Resets the score and stats and clears all the Enemies, Events, Projectiles and Pickups.
     void resetGame();
     /// @brief Saves the current score appending the score.txt file with current time, stage path and score.
     void saveScore();
public:
    /// @brief Class constructor
    Game(); 
    /// @brief Deleted copy constructor to prevent Game object from being copied
    Game(const Game&) = delete;
    /// @brief Deleted copy assignment operator to prevent Game object from being copied
    Game& operator=(const Game&) = delete;
     /// @brief Sets the SFML RenderWindow. Necessary for rendering to work.
     /// @param window - pointer to an SFML RenderWindow.
     void setRenderWindow(sf::RenderWindow* window);
     /// @brief Core method responsible for calling all the process methods and handling game management logic.
     void process();
     /// @brief Core method responsible for calling all the render methods.
     void render();

};