#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameMap.h"
#include "Entity.h"
#include "CollisionDetector.h"

class PlayScene : public Scene {
	LeftPaddle *leftPaddle;
	RightPaddle *rightPaddle;
	ScorePaddle *leftScorePaddle;
	ScorePaddle *rightScorePaddle;
	Ball *ball;
	LPDIRECT3DTEXTURE9 player1_win_texture;
	LPDIRECT3DTEXTURE9 player2_win_texture;

	DWORD showTime;
	DWORD showTimeRate;
	int win;

	GameMap *map;
	Camera *camera;
public:
	PlayScene();
	virtual ~PlayScene();
	virtual void HandleInput();
	virtual void OnMouseMove(float x, float y);
	virtual void Render();
	virtual void Update(double dt);
	void CheckCollision();
	void Reset();
};