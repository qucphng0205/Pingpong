#include "BoxCollider.h"

void BoxCollider::FlipVelX() {
	velX = -velX;
}

void BoxCollider::FlipVelY() {
	velY = -velY;
}
