#include "SeriesInLinePattern.h"

#include "ProjectileFalling.h"
#include "IAddProjectile.h"
#include "ProjectileBuilder.h"
#include "ProjectileStraight.h"
#include "Player.h"
#include "Projectile.h"

void SeriesInLinePattern::attack(Player& player, IAddProjectile& projectiles) {
	static ProjectileBuilder<ProjectileStraight> pbs(projectiles);
	if (shots_left_ > 0) {
		if (--delay_left <= 0) {
			if (--shots_left_ == 0) {
				switch_signal_ = true;
			}
			delay_left = projectile_delay;
			std::unique_ptr<Projectile> projectile =
				pbs.direction(player.getPosition() - position_)
				.position(position_)
				.scale(projectile_scale_)
				.velocity(8.f)
				.build();
			projectiles.createEnemyProjectile(std::move(projectile));
		}
	}
	else if (--until_reload <= 0) {
		switch_signal_ = false;
		until_reload = reload_time_;
		shots_left_ = shots_in_series;
	}
}
