#include "Pickup.h"

void Pickup::process() {
	move(sf::Vector2f{ 0,1.f } *4.f);
	if (position_.y > 900 || position_.y < -500 || position_.x < 0 || position_.x > 1200) {
		disable();
	}
}
const CollisionCircle& Pickup::getHitbox() const {
	return hitbox_;
}

void Pickup::move(sf::Vector2f displacement) {
	position_ += displacement;
	sprite_.setPosition(position_);
	hitbox_.position_ = position_;
}

Pickup::Pickup() {
	sprite_.setTexture(TextureManager::getInstance().getTexture("assets/star128.png"), true);
	sprite_.setOrigin({ 64.f,64.f });
	sprite_.setScale({ 0.40f, 0.40f });
	hitbox_.position_ = position_;
	hitbox_.radius_ = 32;
}