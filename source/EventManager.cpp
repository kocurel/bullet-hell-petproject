#include "EventManager.h"
#include "Event.h"
#include "EnemyManager.h"

void EventManager::process(EnemyManager& enemies, ProjectileManager& projectiles) {
    if (events_.empty()) {
        return;
    }
    if (!waiting_) {
        bool done = events_.front()->countdown();
        if (done) {
            if (events_.front()->get_wait()) {
                waiting_ = true;
            }
            events_.front()->onRelease(enemies, projectiles);
            events_.pop();
        }
    }
}

EventManager::EventManager() {}

void EventManager::endWave() {
    waiting_ = false;
}

bool EventManager::isStageOver() {
    return (events_.empty() && !waiting_);
}

void EventManager::addEvent(std::unique_ptr<Event>&& event) {
    events_.push(std::move(event));
}

void EventManager::clearEvents() {
    while(!events_.empty()) {
        events_.pop();
    }
}