#include "EventFactory.h"

#include <iostream>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Event.h"
#include "IAddEvent.h"
#include "NewEnemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy.h"
#include "ProjectileStraight.h"
#include "NewProjectile.h"

EventFactory::EventFactory(IAddProjectile& projectiles, IAddEvent& event_manager)
    : projectiles_(projectiles),
    event_manager_(event_manager) {
}

void EventFactory::createEvent(int id, bool wait, int countdown) {
    std::unique_ptr<Enemy> enemy;
    std::unique_ptr<Event> event;
    ProjectileBuilder<ProjectileStraight> pb(projectiles_);
    std::unique_ptr<Projectile> projectile;
    switch (id) {
    case 0x010:
        enemy = std::make_unique<Enemy1>(projectiles_);
        enemy->setPosition(sf::Vector2f(701.f, -50.f));
        event = std::make_unique<NewEnemy>(std::move(enemy));
        break;
    case 0x011:
        enemy = std::make_unique<Enemy1>(projectiles_);
        enemy->setPosition(sf::Vector2f(199.f, -50.f));
        event = std::make_unique<NewEnemy>(std::move(enemy));
        break;
    case 0x012:
        enemy = std::make_unique<Enemy1>(projectiles_);
        enemy->setPosition(sf::Vector2f(450.f, -50.f));
        event = std::make_unique<NewEnemy>(std::move(enemy));
        break;
    case 0x020:
        enemy = std::make_unique<Enemy2>(projectiles_);
        enemy->setPosition(sf::Vector2f(450.f, -50.f));
        event = std::make_unique<NewEnemy>(std::move(enemy));
        break;
    case 0x003:
        pb.position({ 450.f,-100 });
        pb.direction({ 0.f,1.f });
        pb.velocity(2.f);
        pb.scale(2.f);
        projectile = pb.build();
        event = std::make_unique<NewProjectile>(std::move(projectile));
        break;
    default:
        std::cout << "Unknown event id: " << id << std::endl;
        return;
    }
    event->setCountdown(countdown);
    event->setWait(wait);
    event_manager_.addEvent(std::move(event));
}
