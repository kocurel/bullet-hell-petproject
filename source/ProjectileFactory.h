#pragma once
#include <memory>
#include <SFML/System/Vector2.hpp>

class Projectile;

enum class ProjectileType {
	ProjectileStraight,
	ProjectileFalling,
};

#include "ProjectileStraight.h"
#include "ProjectileFalling.h"
#include "IProjectileManager.h"

namespace ProjectileFactory {
	std::unique_ptr<Projectile> createProjectile(ProjectileType type, IProjectileManager& projectile_manager,
		sf::Vector2f pos, sf::Vector2f dir, float vel, float scale, sf::Color clr = sf::Color{}) {
		switch (type) {
		case ProjectileType::ProjectileStraight:
			return std::make_unique<ProjectileStraight>(projectile_manager, pos, dir, vel, scale, clr);
		default:
			return nullptr;
		}
	}
}