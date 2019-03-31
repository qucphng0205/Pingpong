#pragma once
#include "Graphic.h"
#include "Textures.h"
#include "Sprites.h"
#include "GameConfig.h"
#include "MyHelper.h"
#include "Paddle.h"
#include "Entity.h"
class Ball : public Entity {
	static bool hasLoadResources;
	DWORD collideTime;
	DWORD collideRate;
	Sprite *sprite;
public:
	Ball();
	void LoadResources();
	void Update(double dt);
	void Render();
	void FlipVelX();
	void FlipVelY();
	bool CheckCollidePaddle(Paddle *paddle);
};