#pragma once
#include "Graphic.h"
#include "Textures.h"
#include "Sprites.h"
#include "GameConfig.h"
#include "MyHelper.h"
#include "Paddle.h"
#include "Entity.h"
#include "Animation.h"

class Ball : public Entity {
	static bool hasLoadResources;
	DWORD collideTime;
	DWORD collideRate;
	Animation *anim;
public:
	Ball();
	void LoadResources();
	void Update(double dt);
	void Render();
	void FlipVelX();
	void FlipVelY();
	void SetRandomVelocity() {
		srand(time(NULL));
		velocity.x = rand() % (BALL_SPEED * 2 + 1) + -BALL_SPEED;
		velocity.y = sqrt(pow(BALL_SPEED, 2) - pow(velocity.x, 2));
	}
	void OnCollision(Entity *impactor, CollisionReturn data, SideCollision side, int &goal);
	void OnCollision(Entity *impactor, SideCollision side, int &goal);
};