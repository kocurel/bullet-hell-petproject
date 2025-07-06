#include "PickupManager.h"
#include "PickupClasses.h"
#include <iostream>

void PickupManager::cleanup() {
	if (--cleanup_counter_ <= 0) {
		cleanup_counter_ = 360;
		auto it = std::remove_if(pickups_.begin(), pickups_.end(), [](std::unique_ptr<Pickup>& obj) {return obj->isDisabled(); });
		pickups_.erase(it, pickups_.end());
	}
}

void PickupManager::clearPickups() {
	pickups_.clear();
}

const std::vector<std::unique_ptr<Pickup>>& PickupManager::getPickups() {
	return pickups_;
};

void PickupManager::process() {
	cleanup();
	for (auto& pickup : pickups_
		| std::views::filter([](std::unique_ptr<Pickup>& obj) {return !obj->isDisabled(); })) {
		pickup->process();
	}

}

void PickupManager::renderPickups(sf::RenderWindow& window) {
	for (auto& pickup : pickups_
		| std::views::filter([](std::unique_ptr<Pickup>& obj) {return !obj->isDisabled(); })) {
		pickup->render(window);
	}

}

std::mutex& PickupManager::getMutex() {
	return mtx_;
}

void PickupManager::createPickup(int type, sf::Vector2f posistion) {
	std::lock_guard lck(mtx_);
	std::unique_ptr<Pickup> pickup_new;

	switch (type) {
	case 0:
		pickup_new = std::make_unique<PickupHealth>();
		pickup_new->setPosition(posistion);
		pickups_.push_back(std::move(pickup_new));
		break;
	case 1:
		pickup_new = std::make_unique<PickupAttackUp>();
		pickup_new->setPosition(posistion);
		pickups_.push_back(std::move(pickup_new));
		break;
	case 2:
		pickup_new = std::make_unique<PickupAttackPattern>();
		pickup_new->setPosition(posistion);
		pickups_.push_back(std::move(pickup_new));
		break;
	case 3:
		pickup_new = std::make_unique<PickupBomb>();
		pickup_new->setPosition(posistion);
		pickups_.push_back(std::move(pickup_new));
		break;
	default:
		std::cout << "Undefined pickup type: " << type << std::endl;
		break;
	}

}

PickupManager::~PickupManager() {}
