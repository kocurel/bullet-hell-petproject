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

void PickupManager::clear() {
	pickups_.clear();
}

void PickupManager::process() {
	cleanup();
	for (auto& pickup : pickups_
		| std::views::filter([](std::unique_ptr<Pickup>& obj) {return !obj->isDisabled(); })) {
		pickup->process();
	}

}

void PickupManager::render(sf::RenderWindow& window) {
	for (auto& pickup : pickups_
		| std::views::filter([](std::unique_ptr<Pickup>& obj) {return !obj->isDisabled(); })) {
		pickup->render(window);
	}

}

void PickupManager::createPickup(std::unique_ptr<Pickup>&& pickup) {
	if (pickup) {
		pickups_.push_back(std::move(pickup));
	}
	else {
		throw std::invalid_argument("Pickup passed to the PickupManager was nullptr");
	}
}

PickupManager::~PickupManager() {}
