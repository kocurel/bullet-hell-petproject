#include "PickupFactory.h"
#include "PickupClasses.h"

std::unique_ptr<Pickup> PickupFactory::createPickup(PickupType type, sf::Vector2f position) {
    std::unique_ptr<Pickup> pickup;
    switch (type) {
    case PickupType::Health: 
        return std::make_unique<PickupHealth>(position);
    case PickupType::AttackUp: 
        return std::make_unique<PickupAttackUp>(position);
    case PickupType::AttackPattern: 
        return std::make_unique<PickupAttackPattern>(position);
    case PickupType::Bomb:
        return std::make_unique<PickupBomb>(position);
    default:
        throw std::invalid_argument("PickupType not defined in PickupFactory: " +
            std::to_string(static_cast<int>(type)));
    }
}
