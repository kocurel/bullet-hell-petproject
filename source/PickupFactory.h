#pragma once
#include <memory>
#include <SFML/System/Vector2.hpp>
class Pickup;

enum class PickupType {
    Health,
    AttackUp,
    AttackPattern,
    Bomb,
};

namespace PickupFactory {
    /// @brief Creates a Pickup unique_pointer to a PickupObject.
    /// @param type - PickupType enum for the type of pickup to be created
    /// @param position - Vector2f position of the pickup created
    /// @return - Returns a unique_pointer to the newly created Pickup.
    std::unique_ptr<Pickup> createPickup(PickupType type, sf::Vector2f position);
}