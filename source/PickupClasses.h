/// @file PickupClasses.h
/// @brief declares all the different Pickup subclasses.
#pragma once
#include "Pickup.h"
#include "Player.h"
#include "TextureManager.h"
#include <SFML/System/Vector2.hpp>

/// @brief A pickup that increases Player's attack speed.
class PickupAttackUp : public Pickup {
public:
	PickupAttackUp(sf::Vector2f position) {
		position_ = position;
		sprite_.setColor(sf::Color(240, 0, 0));
	}
	void onPickup(Player& player) override {
		disable();
		player.AttackSpeedUp();
	};
};

/// @brief A pickup that increases Player's health.
class PickupHealth : public Pickup {
public:
	PickupHealth(sf::Vector2f position) {
		position_ = position;
		sprite_.setColor(sf::Color(0, 240, 0));
	}
	void onPickup(Player& player) override {
		disable();
		player.increaseHealth();
	};
};

/// @brief A pickup that changes the Player's attack pattern.
class PickupAttackPattern : public Pickup {
public:
	PickupAttackPattern(sf::Vector2f position) {
		position_ = position;
		sprite_.setColor(sf::Color(255, 223, 0));
	}
	void onPickup(Player& player) override {
		disable();
		player.nextAttackPattern();
	};
};

/// @brief A pickup that increases the number of Player's bombs.
class PickupBomb : public Pickup {
public:
	PickupBomb(sf::Vector2f position) {
		position_ = position;
		sprite_.setColor(sf::Color(255, 133, 25));
	}
	void onPickup(Player& player) override {
		disable();
		player.increaseBomb();
	};
};