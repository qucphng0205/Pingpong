#pragma once
#include "GameConfig.h"
#include "Textures.h"
#include "Graphic.h"
#include <d3dx9.h>
#include "Debug.h"
#include "Entity.h"
#include "Sprites.h"

class Paddle : public Entity{
protected:
	static bool hasLoadResources;
	Sprite *sprite;
public:
	Paddle();
	virtual void LoadResources();
	virtual void Render();
	virtual void Update(double dt);
};

class LeftPaddle : public Paddle {
public:
	LeftPaddle();
	void MoveUp();
	void MoveDown();
	void Idle();
};

class RightPaddle : public Paddle {
public:
	RightPaddle();
	void HandleMouse(float x, float y);
	virtual void Update(double dt);
private:
	float posMouseY;
};

class ScorePaddle : public Paddle {
public:
	ScorePaddle() {
		LoadResources();
	};
	virtual void LoadResources();
};
