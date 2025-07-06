#include "Game.h"

#include "Player.h"
#include "EventParser.h"
#include "EventManager.h"
#include "EnemyManager.h"
#include "ProjectileManager.h"
#include "UserInterface.h"
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "Enemy.h"
#include <fstream>

Game::Game() : parser_(projectiles_, event_manager_), enemy_manager_(event_manager_), player_(projectiles_) {}

void Game::processPlayer(Game& instance) {
    instance.player_.process(instance.projectiles_, instance.pickup_manager_);
}

void Game::processEnemies(Game& instance) {
    instance.enemy_manager_.process(instance.player_, instance.projectiles_, instance.pickup_manager_);
}

void Game::setRenderWindow(sf::RenderWindow* window) {
    window_ = window;
}
void Game::checkLevelSelection() {
    using sf::Keyboard::Key;
    InputManager& input_manager = InputManager::getInstance();
    if (input_manager.isKeyJustPressed(Key::Num1)) {
        resetGame();
        parser_.load(0);
        stage_selection = false;
    }
    if (input_manager.isKeyJustPressed(Key::Num2)) {
        resetGame();
        parser_.load(1);
        stage_selection = false;
    }
    if (input_manager.isKeyJustPressed(Key::Num3)) {
        resetGame();
        parser_.load(2);
        stage_selection = false;
    }
    if (input_manager.isKeyJustPressed(Key::Num4)) {
        resetGame();
        parser_.load(3);
        stage_selection = false;
    }
    if (input_manager.isKeyJustPressed(Key::Num5)) {
        resetGame();
        parser_.load(4);
        stage_selection = false;
    }
    if (input_manager.isKeyJustPressed(Key::Num6)) {
        resetGame();
        parser_.load(5);
        stage_selection = false;
    }
    if (input_manager.isKeyJustPressed(Key::Num7)) {
        resetGame();
        parser_.load(6);
        stage_selection = false;
    }
    if (input_manager.isKeyJustPressed(Key::Num8)) {
        resetGame();
        parser_.load(7);
        stage_selection = false;
    }
    if (input_manager.isKeyJustPressed(Key::Num9)) {
        resetGame();
        parser_.load(8);
        stage_selection = false;
    }
}

void Game::saveScore() {
    std::ofstream file("scores.txt", std::ios_base::app);
    auto now = std::chrono::system_clock::now();
    time_t t = time(NULL);
    file << "Local time: " << asctime(localtime(&t))
        << " Stage: "
        << parser_.getPath()
        << " SCORE: "
        << UserInterface::getInstance().getScore() 
        << std::endl;
    file.close();
}
void Game::resetGame() {

    projectiles_.clearProjectiles();
    player_.resetPlayer();
    pickup_manager_.clearPickups();
    enemy_manager_.clearEnemies();
    event_manager_.clearEvents();
    player_.setPosition({ 450.f, 600.f });
    UserInterface::getInstance().updateLife(3);
    UserInterface::getInstance().resetScore();
}

void Game::process() {

    if (player_.getHealthPoints() <= 0 && !stage_selection) {
        game_over_ = true;
    }
    if (game_over_ || stage_finished_) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            game_over_ = false;
            stage_finished_ = false;
            stage_selection = true;
            resetGame();
        }
        return;
    }
    if (!stage_selection && event_manager_.isStageOver()) {
        if (UserInterface::getInstance().getScore() > 0) {
            stage_finished_ = true;
            saveScore();
        }
        else {
            stage_selection = true;
        }
    }
    if (stage_selection) {
        checkLevelSelection();
        return;
    }
    event_manager_.process(enemy_manager_, projectiles_);
    std::jthread player_thread(&processPlayer, std::ref(*this));
    std::jthread enemy_thread(&processEnemies, std::ref(*this));
    player_thread.join();
    enemy_thread.join();
    projectiles_.process();
    pickup_manager_.process();
}

void Game::render() {

    sf::RenderWindow& window = *window_;
    window.clear();
    UserInterface::getInstance().renderBottom(window);
    player_.render(window);
    pickup_manager_.renderPickups(window);
    projectiles_.render(window);
    enemy_manager_.renderEnemies(window);
    UserInterface::getInstance().renderTop(window);

    if (stage_selection) {
        UserInterface::getInstance().renderSelection(window);
    }
    if (stage_finished_) {
        UserInterface::getInstance().renderStageOver(window);
    }
    if (game_over_) {
        UserInterface::getInstance().renderGameOver(window);
    }
}