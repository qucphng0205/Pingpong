#include "Ball.h"

bool Ball::hasLoadResources = false;

Ball::Ball() {
	LoadResources();
}

void Ball::LoadResources() {
	if (!hasLoadResources) {
		Textures::GetInstance()->Add(TEX_BALL_ID, "Resources/ball.png", D3DCOLOR_XRGB(0, 0, 0));
	}
	auto texture = Textures::GetInstance()->Get(TEX_BALL_ID);
	if (texture == NULL)
		return;
	sprite = new Sprite(RECT(), texture);

	height = sprite->GetHeight();
	width = sprite->GetWidth();

	collideTime = 0;
	collideRate = 200;
}

void Ball::Update(double dt) {
	auto bufferHeight = Graphic::GetInstance()->GetBackBufferHeight();
	auto bufferWidth = Graphic::GetInstance()->GetBackBufferWidth();
	if (position.y <= 0 || position.y + height >= bufferHeight)
		FlipVelY();
	if (position.x <= 0 || position.x + width >= bufferWidth)
		FlipVelX();

	position.x = MyHelper::Clamp(position.x, 0, bufferWidth - width);
	position.y = MyHelper::Clamp(position.y, 0, bufferHeight - height);

	Entity::Update(dt);
}

void Ball::Render() {
	sprite->Draw(position);
}

void Ball::FlipVelX() {
	velocity.x = -velocity.x;
}

void Ball::FlipVelY() {
	velocity.y = -velocity.y;
}

bool Ball::CheckCollidePaddle(Paddle *paddle) {
	bool collide = false;
	if (collideTime > GetTickCount())
		return collide;

	//Check Top AND Bottom

	if (collide)
		collideTime = GetTickCount() + collideRate;
	return collide;
}

