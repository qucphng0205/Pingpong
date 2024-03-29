#include "Ball.h"

bool Ball::hasLoadResources = false;

Ball::Ball() {
	LoadResources();
}

void Ball::LoadResources() {
	if (!hasLoadResources) {
		Textures::GetInstance()->Add(TEX_BALL_ID, "Resources/ahihi2.png", D3DCOLOR_XRGB(0, 0, 0));
	}
	auto texture = Textures::GetInstance()->Get(TEX_BALL_ID);
	if (texture == NULL)
		return;

	anim = new Animation();
	anim->AddFrames(texture, 6, 8, 0.2);

	height = anim->GetHeightCurrentFrame();
	width = anim->GetWidthCurrentFrame();

	collideTime = 0;
	collideRate = 200;
}

void Ball::Update(double dt) {
	anim->Update(dt);

	auto bufferHeight = Graphic::GetInstance()->GetBackBufferHeight();
	auto bufferWidth = Graphic::GetInstance()->GetBackBufferWidth();


	Entity::Update(dt);

	position.x = MyHelper::Clamp(position.x, 0 + width / 2, bufferWidth - width / 2);
	position.y = MyHelper::Clamp(position.y, 0 + height / 2, bufferHeight - height / 2);

	if (position.y - height / 2 <= 0 || position.y + height / 2 >= bufferHeight)
		FlipVelY();
	if (position.x - width / 2 <= 0 || position.x + width / 2 >= bufferWidth)
		FlipVelX();
}

void Ball::Render() {
	anim->Render(position);
}

void Ball::FlipVelX() {
	velocity.x = -velocity.x;
}

void Ball::FlipVelY() {
	velocity.y = -velocity.y;
}

void Ball::OnCollision(Entity * impactor, CollisionReturn data, SideCollision side, int &goal) {
	if (!data.IsCollided)
		return;
	auto colTag = impactor->GetTag();
	if (colTag == LeftGoal) {
		//goal = 2;
		return;
	}
	else
		if (colTag == RightGoal) {
			//goal = 1;
			return;
		}
	goal = 0;
	if (side == NotKnow)
		return;
	if (side == Corner) {
		FlipVelX();
		FlipVelY();
	}
	else
		if (side == Top || side == Bottom)
			FlipVelY();
		else
			FlipVelX();
}

void Ball::OnCollision(Entity * impactor, SideCollision side, int & goal) {
	auto colTag = impactor->GetTag();
	if (colTag == LeftGoal) {
		//goal = 2;
		return;
	}
	else
		if (colTag == RightGoal) {
			//goal = 1;
			return;
		}
	goal = 0;
	if (side == Top || side == Bottom)
		FlipVelY();
	else
		FlipVelX();
}

