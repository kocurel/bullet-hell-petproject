#include "TripleStraightPattern.h"

#include "IProjectileManager.h"
#include "ProjectileBuilder.h"
#include "ProjectileStraight.h"
#include "IPlayer.h"
#include "Projectile.h"

void TripleStraightPattern::attack(IPlayer& player, IProjectileManager& projectiles) {
    if (--until_reload_ > 0) {
        switch_signal_ = false;
        return;
    }
    until_reload_ = reload_time_;

    sf::Vector2f direction1 = player.getPosition() - position_;
    sf::Vector2f direction2 = rotateVector(direction1, 30);
    sf::Vector2f direction3 = rotateVector(direction1, -30);

    ProjectileBuilder<ProjectileStraight> ps_builder(projectiles);
    ps_builder
        .direction(direction1)
        .position(position_)
        .velocity(bullet_speed_);
    std::unique_ptr<Projectile> projectile1 = ps_builder.build();

    ps_builder
        .direction(direction2);
    std::unique_ptr<Projectile> projectile2 = ps_builder.build();

    ps_builder
        .direction(direction3);
    std::unique_ptr<Projectile> projectile3 = ps_builder.build();
    projectiles.addEnemyProjectile(std::move(projectile1));
    projectiles.addEnemyProjectile(std::move(projectile3));
    projectiles.addEnemyProjectile(std::move(projectile2));
    switch_signal_ = true;
}