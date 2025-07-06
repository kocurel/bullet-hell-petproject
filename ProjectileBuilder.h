/// @file ProjectileBuilder.h
/// @brief declares the ProjectileBuilder class
#pragma once

#include <concepts>
#include "Projectile.h"
#include "IAddProjectile.h"

/// @brief Concept to check if a type `T` is derived from a base type `U`.
/// @tparam T - The type to check if it's derived.
/// @tparam U - The base type.
template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

/// @brief A builder class for constructing Projectile objects.
///
/// This class implements the Builder design pattern, allowing for a fluent
/// interface to set various properties of a projectile before constructing it.
/// It is templated to create specific types of projectiles derived from `Projectile`.
/// @tparam T The concrete type of Projectile to build, which must be derived from `Projectile`.
template<Derived<Projectile> T>
class ProjectileBuilder {
private:
    /// @brief Reference to an interface for adding projectiles to a collection.
    /// This is passed to the constructed projectile's constructor.
    IAddProjectile& projectiles_;

    /// @brief The scale factor for the projectile's sprite.
    float scale_ = 0.75f;

    /// @brief The damage value of the projectile.
    float damage_ = 1.f;

    /// @brief The velocity (speed) of the projectile.
    float velocity_ = 1.f;

    /// @brief The initial position of the projectile.
    sf::Vector2f position_;

    /// @brief The direction of the projectile.
    sf::Vector2f direction_;

    /// @brief The color tint of the projectile's sprite.
    sf::Color color_ = sf::Color(255, 255, 255, 255);

    /// @brief The maximum allowed velocity for the projectile.
    float max_velocity_ = 1000000.f;

public:
    /// @brief Constructor for the ProjectileBuilder.
    /// @param projectiles A reference to an IAddProjectile interface, which will be passed to the constructed projectile.
    explicit ProjectileBuilder(IAddProjectile& projectiles) : projectiles_(projectiles) {};

    /// @brief Sets the color tint for the projectile.
    /// @param clr The sf::Color to set.
    /// @return A reference to the builder for method chaining.
    ProjectileBuilder& color(const sf::Color clr) {
        color_ = clr;
        return *this;
    }

    /// @brief Sets the scale factor for the projectile's sprite.
    /// @param scale The float scale value.
    /// @return A reference to the builder for method chaining.
    ProjectileBuilder& scale(const float scale) {
        scale_ = scale;
        return *this;
    }

    /// @brief Sets the initial position of the projectile.
    /// @param pos The sf::Vector2f position.
    /// @return A reference to the builder for method chaining.
    ProjectileBuilder& position(const sf::Vector2f pos) {
        position_ = pos;
        return *this;
    }

    /// @brief Sets the movement direction of the projectile.
    /// The input vector will be normalized.
    /// @param dir The sf::Vector2f direction.
    /// @return A reference to the builder for method chaining.
    ProjectileBuilder& direction(const sf::Vector2f dir) {
        direction_ = dir.normalized();
        return *this;
    }

    /// @brief Sets the damage value of the projectile.
    /// @param dmg The float damage value.
    /// @return A reference to the builder for method chaining.
    ProjectileBuilder& damage(const float dmg) {
        damage_ = dmg;
        return *this;
    }

    /// @brief Sets the velocity (speed) of the projectile.
    /// @param vel The float velocity value.
    /// @return A reference to the builder for method chaining.
    ProjectileBuilder& velocity(const float vel) {
        velocity_ = vel;
        return *this;
    }

    /// @brief Sets the maximum velocity for the projectile.
    /// @param vel The float maximum velocity value.
    /// @return A reference to the builder for method chaining.
    ProjectileBuilder& max_velocity(const float vel) {
        max_velocity_ = vel;
        return *this;
    }

    /// @brief Constructs and returns a unique pointer to the configured projectile.
    /// @return A std::unique_ptr to the newly created projectile of type T.
    std::unique_ptr<T> build() const {
        std::unique_ptr<T> projectile = std::make_unique<T>(projectiles_, scale_);

        T& proj = *projectile;
        proj.setPosition(position_);
        proj.setDirection(direction_);
        proj.setVelocity(velocity_);
        proj.setColor(color_);
        proj.setDamage(damage_);
        proj.setMaxVelocity(max_velocity_);

        return std::move(projectile);
    }
};
