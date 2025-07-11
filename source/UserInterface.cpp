#include "UserInterface.h"
#include <string>
#include "TextureManager.h"

UserInterface& UserInterface::getInstance() {
    static UserInterface instance_;
    return instance_;
}

UserInterface::UserInterface() 
    :   font_("assets/Sono-SemiBold.ttf"),
        score_text_(font_),
        game_over_text_(font_),
        selection_text_(font_),
        stage_over_text_(font_),
        game_over_score_text_(font_),
        heart_(TextureManager::getInstance().getTexture("assets/heart128.png")),
        bomb_(TextureManager::getInstance().getTexture("assets/bomb128.png"))
{
    
    heart_.scale(sf::Vector2f(0.5f, 0.5f));
    bomb_.scale(sf::Vector2f(0.5f, 0.5f));

    selection_text_.setString("SELECT STAGE NUMBER");
    selection_text_.setCharacterSize(60);
    selection_text_.setPosition({ 240, 250.f });

    game_over_text_.setString("GAME OVER");
    game_over_text_.setCharacterSize(60);
    game_over_text_.setPosition({ 270, 250.f });

    stage_over_text_.setString("STAGE OVER");
    stage_over_text_.setCharacterSize(60);
    stage_over_text_.setPosition({ 270, 250.f });


    game_over_score_text_.setCharacterSize(60);
    game_over_score_text_.setPosition({ 320, 360.f });

    score_text_.setString("SCORE:\n000000");
    score_text_.setCharacterSize(44);
    score_text_.setPosition({ 805.f, 350.f });

    shadow_overlay_.setFillColor(sf::Color(0, 0, 0, 100));
    shadow_overlay_.setPosition({ 0, 0 });
    shadow_overlay_.setSize({ 1120, 840 });

    game_space_.setFillColor(sf::Color(40, 40, 40, 255));
    game_space_.setPosition({ 150, 20 });
    game_space_.setSize({ 600, 800 });

    black_bar1_.setFillColor(sf::Color(0, 0, 0, 255));
    black_bar1_.setPosition({ 0, 0 });
    black_bar1_.setSize({ 1120, 20 });

    black_bar2_.setFillColor(sf::Color(0, 0, 0, 255));
    black_bar2_.setPosition({ 0, 0 });
    black_bar2_.setSize({ 150, 840 });

    black_bar3_.setFillColor(sf::Color(0, 0, 0, 255));
    black_bar3_.setPosition({ 0, 820 });
    black_bar3_.setSize({ 1120, 800 });

    black_bar4_.setFillColor(sf::Color(0, 0, 0, 255));
    black_bar4_.setPosition({ 750, 0 });
    black_bar4_.setSize({ 370, 820 });
}

void UserInterface::renderSelection(sf::RenderWindow& window) {
    window.draw(shadow_overlay_);
    window.draw(selection_text_);
}

void UserInterface::renderGameOver(sf::RenderWindow& window) {
    window.draw(shadow_overlay_);
    window.draw(game_over_text_);
    game_over_score_text_.setString(score_text_.getString());
    window.draw(game_over_score_text_);
}
void UserInterface::renderStageOver(sf::RenderWindow& window) {
    window.draw(shadow_overlay_);
    window.draw(stage_over_text_);
    game_over_score_text_.setString(score_text_.getString());
    window.draw(game_over_score_text_);
}
void UserInterface::resetScore() {
    score_value_ = 0;
    std::string text = std::to_string(score_value_);
    text.insert(text.begin(), 6 - text.length(), '0');
    score_text_.setString("SCORE:\n" + text);
}

int UserInterface::getScore() {
    return score_value_;
}

void UserInterface::updateLife(int life) {
    life_ = life;
}

void UserInterface::updateBombs(int bombs) {
    bombs_ = bombs;
}

void UserInterface::increaseScore(int value) {
    score_value_ += value;
    std::string text = std::to_string(score_value_);
    text.insert(text.begin(), 6 - text.length(), '0');
    score_text_.setString("SCORE:\n" + text);
}

void UserInterface::renderBottom(sf::RenderWindow& window) {
    window.draw(game_space_);
}

void UserInterface::renderTop(sf::RenderWindow& window) {
    window.draw(black_bar1_);
    window.draw(black_bar2_);
    window.draw(black_bar3_);
    window.draw(black_bar4_);
    window.draw(score_text_);
    if (life_ >= 1) {
        heart_.setPosition({ 800, 480 });
        window.draw(heart_);
    }
    if (life_ >= 2) {
        heart_.setPosition({ 860, 480 });
        window.draw(heart_);
    }
    if (life_ >= 3) {
        heart_.setPosition({ 920, 480 });
        window.draw(heart_);
    }
    if (bombs_ >= 1) {
        bomb_.setPosition({ 805, 580 });
        window.draw(bomb_);
    }
    if (bombs_ >= 2) {
        bomb_.setPosition({ 865, 580 });
        window.draw(bomb_);
    }
    if (bombs_ >= 3) {
        bomb_.setPosition({ 925, 580 });
        window.draw(bomb_);
    }
}