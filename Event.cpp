#include "Event.h"
#include "EnemyManager.h"

bool Event::get_wait() const {
    return wait_;
}

void Event::setWait(bool wait) {
    wait_ = wait;
}

void Event::setCountdown(int frames) {
    frames_countdown_ = frames;
}

bool Event::countdown() {
    if (--frames_countdown_ <= 0) {
        return true;
    }
    return false;
}