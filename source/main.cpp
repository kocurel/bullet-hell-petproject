#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include <Windows.h>
#include "InputManager.h"
#include <optional>

constexpr auto LAG_WARNING = 1;
#define WINDOW_X 1120
#define WINDOW_Y 840

int main() {
    TextureManager::getInstance().loadAllTextures({
            "assets/circle64.png",
            "assets/heart128.png",
            "assets/star128.png",
            "assets/bomb128.png"
        }
    );
    sf::Font font;
    if (!font.openFromFile("assets/Sono-SemiBold.ttf")) {
        system("PAUSE");
        return 1;
    }
    std::map<sf::Keyboard::Key, bool> a;
    sf::RenderWindow window(sf::VideoMode({ WINDOW_X, WINDOW_Y }), "Game Window", sf::Style::Close);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    Game game;
    game.setRenderWindow(&window);
    InputManager& input_manager = InputManager::getInstance();


    while (window.isOpen()) {
        auto time1 = std::chrono::steady_clock::now().time_since_epoch();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (event->is<sf::Event::KeyPressed>())
                input_manager.setKeyJustPressed(event->getIf<sf::Event::KeyPressed>()->code);
        }
        game.process();

        game.render();

        window.display();

        InputManager::getInstance().clearInputs();
        if (LAG_WARNING) {
            auto time2 = std::chrono::steady_clock::now().time_since_epoch();  
            auto time_passed = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1);
            if (time_passed > std::chrono::milliseconds(60) ) {
                std::cout << "lag, fps: " << (std::chrono::milliseconds(1000) / time_passed) << '\n';
            }
        }
    }
    return 0;
}