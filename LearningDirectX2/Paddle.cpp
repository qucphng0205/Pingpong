#include "Paddle.h"
bool Paddle::hasLoadResources = false;
Paddle::Paddle() {
	LoadResources();
}
void Paddle::LoadResources() {
	if (!hasLoadResources) {
		Textures::GetInstance()->Add(TEX_PADDLE_ID, "Resources\\paddle.png", NULL);
		Textures::GetInstance()->Add(TEX_SCOREPADDLE_ID, "Resources\\scorepaddle.png", NULL);
	}
	auto texture = Textures::GetInstance()->Get(TEX_PADDLE_ID);
	if (texture == NULL)
		return;
	sprite = new Sprite(RECT(), texture);
	height = sprite->GetHeight();
	width = sprite->GetWidth();
	hasLoadResources = true;
}

void Paddle::Render() {
	sprite->Draw(position);
}

void Paddle::Update(double dt) {
	auto bufferHeight = Graphic::GetInstance()->GetBackBufferHeight();
	Entity::Update(dt);
	position.y = MyHelper::Clamp(position.y, 0, bufferHeight - height);
}
//
void LeftPaddle::MoveUp() {
	velocity.y = -PADDLE_SPEED;
}
void LeftPaddle::MoveDown() {
	velocity.y = PADDLE_SPEED;
}
void LeftPaddle::Idle() {
	velocity.y = 0;
}
//
void RightPaddle::HandleMouse(float x, float y) {
	posMouseY = y;
	posMouseY = MyHelper::Clamp(y, height / 2, Graphic::GetInstance()->GetBackBufferHeight() - height / 2);
	if (position.y > posMouseY) 
		velocity.y = -PADDLE_SPEED;
	else 
		velocity.y = PADDLE_SPEED;
}

void RightPaddle::Update(double dt) {
	if (velocity.y == 0) return;

	auto bufferHeight = Graphic::GetInstance()->GetBackBufferHeight();

	Entity::Update(dt);
	if (velocity.y > 0) {
		if (position.y > posMouseY) {
			position.y = posMouseY;
			velocity.y = 0;
		}
	}
	else if (position.y < posMouseY) {
		position.y = posMouseY;
		velocity.y = 0;
	}
	DebugOut(L"%f + %f\n", position.y, posMouseY);
}

void ScorePaddle::LoadResources() {
	if (!hasLoadResources) {
		Textures::GetInstance()->Add(TEX_SCOREPADDLE_ID, "Resources\\PixelCharacter.png", NULL);
	}
	auto texture = Textures::GetInstance()->Get(TEX_SCOREPADDLE_ID);
	if (texture == NULL)
		return;

	sprite = new Sprite(RECT(), texture);

	height = sprite->GetHeight();
	width = sprite->GetWidth();
	hasLoadResources = true;
}
