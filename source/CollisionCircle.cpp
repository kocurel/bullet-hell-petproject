#include "CollisionCircle.h"

CollisionCircle::CollisionCircle()
    : position_({ 0, 0 }), radius_(0) {}

bool CollisionCircle::checkCollision(const CollisionCircle& other) const {
    float distance = (position_ - other.position_).length();
    float sum_of_radii = radius_ + other.radius_;
    return (distance < sum_of_radii);
}