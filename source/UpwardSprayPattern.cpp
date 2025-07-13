#include "UpwardSprayPattern.h"

#include "ProjectileFalling.h"
#include "IProjectileManager.h"
#include "ProjectileBuilder.h"
#include "Player.h"
#include "Projectile.h"

void UpwardSprayPattern::attack(IPlayer& player, IProjectileManager& projectiles) {
	static ProjectileBuilder<ProjectileFalling> pbs(projectiles);
	if (shots_left_ > 0) {
		if (--delay_left <= 0) {
			if (--shots_left_ == 0) {
				switch_signal_ = true;
				direction_ = sf::Vector2f{ 1.f, -1.f };
			}
			delay_left = projectile_delay;
			std::unique_ptr<Projectile> projectile =
				pbs.direction(direction_)
				.position(position_)
				.scale(projectile_scale_)
				.velocity(velocity)
				.scale(scale)
				.build();
			projectiles.addEnemyProjectile(std::move(projectile));
			direction_ = rotateVector(direction_, -18);
		}
	}
	else if (--until_reload <= 0) {
		switch_signal_ = false;
		until_reload = reload_time_;
		shots_left_ = shots_in_series;
		direction_ = sf::Vector2f{ 1.f, -0.8f };
	}
}
void UpwardSprayPattern::setReloadTime(int frames) {
	reload_time_ = frames;
}