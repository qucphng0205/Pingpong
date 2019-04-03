#include "PlayScene.h"

PlayScene::PlayScene() {
	//LoadResources
	auto bufferHeight = Graphic::GetInstance()->GetBackBufferHeight();
	auto bufferWidth = Graphic::GetInstance()->GetBackBufferWidth();

	Textures::GetInstance()->Add(TEX_PLAYER1_WIN_ID, "Resources\\player1win.png", D3DCOLOR_XRGB(255, 255, 255));
	Textures::GetInstance()->Add(TEX_PLAYER2_WIN_ID, "Resources\\player2win.png", D3DCOLOR_XRGB(255, 255, 255));

	player1_win_texture = Textures::GetInstance()->Get(TEX_PLAYER1_WIN_ID);
	player2_win_texture = Textures::GetInstance()->Get(TEX_PLAYER2_WIN_ID);
	leftPaddle = new LeftPaddle();
	rightPaddle = new RightPaddle();
	leftScorePaddle = new ScorePaddle();
	leftScorePaddle->SetTag(Entity::LeftGoal);
	rightScorePaddle = new ScorePaddle();
	rightScorePaddle->SetTag(Entity::RightGoal);

	ball = new Ball();

	Reset();
	showTimeRate = 1000;

	map = new GameMap();

	/*int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();
	map = new GameMap((char*)"Resources/bigImage.png", 32, 32);
	map->SetMapPath((char*)"Resources/Output.txt");
	camera = new Camera(width, height);
	camera->SetPosition(D3DXVECTOR3(width / 2, map->GetHeight() - height / 2, 0));
	map->SetCamera(camera);*/
}

PlayScene::~PlayScene() {

}

void PlayScene::HandleInput() {
	while (!KeyBoard::GetInstance()->isEmpty()) {
		KeyEvent e = KeyBoard::GetInstance()->readKey();
		char keyCode = e.GetKeyCode();
		if (keyCode == VK_UP) {
			if (e.IsPress())
				leftPaddle->MoveUp();
			else
				if (!KeyBoard::GetInstance()->isPress(VK_DOWN))
					leftPaddle->Idle();
		}
		else if (keyCode == VK_DOWN) {
			if (e.IsPress())
				leftPaddle->MoveDown();
			else
				if (!KeyBoard::GetInstance()->isPress(VK_UP))
					leftPaddle->Idle();
		}
	}
}

void PlayScene::OnMouseMove(float x, float y) {
	rightPaddle->HandleMouse(x, y);
}


void PlayScene::Render() {
	//map->Draw();
	if (GetTickCount() < showTime) {
		if (win == 1) Graphic::GetInstance()->Draw(0, 0, player1_win_texture);
		else
			Graphic::GetInstance()->Draw(0, 0, player2_win_texture);
		return;
	}
	leftPaddle->Render();
	rightPaddle->Render();
	leftScorePaddle->Render();
	rightScorePaddle->Render();
	ball->Render();
}

void PlayScene::Update(double dt) {
	if (GetTickCount() < showTime)
		return;
	if (win != 0)
		Reset();
	win = 0;
	CheckCollision();

	if (win != 0) {
		showTime = GetTickCount() + showTimeRate;
		return;
	}

	HandleInput();

	Entity::SideCollision side;

	float collisionTime = CollisionDetector::SweptAABB(leftPaddle, ball, side, dt);
	leftPaddle->Update(dt * collisionTime);
	collisionTime = CollisionDetector::SweptAABB(rightPaddle, ball, side, dt);
	rightPaddle->Update(dt * collisionTime);

	collisionTime = 1;

	auto mSide = side;
	float ct1 = CollisionDetector::SweptAABB(ball, leftPaddle, mSide, dt);
	if (ct1 != 1) {
		collisionTime = ct1;
		side = mSide;
	}
	float ct2 = CollisionDetector::SweptAABB(ball, rightPaddle, mSide, dt);
	if (ct2 != 1 && ct2 < collisionTime) {
		collisionTime = ct2;
		side = mSide;
	}
	float ct3 = CollisionDetector::SweptAABB(ball, leftScorePaddle, mSide, dt);
	if (ct3 != 1 && ct3 < collisionTime) {
		collisionTime = ct3;
		side = mSide;
	}
	float ct4 = CollisionDetector::SweptAABB(ball, rightScorePaddle, mSide, dt);
	if (ct4 != 1 && ct4 < collisionTime) {
		collisionTime = ct4;
		side = mSide;
	}

	ball->Update(dt * collisionTime);
	if (collisionTime != 1)
		ball->SetSide(side);
}

void PlayScene::CheckCollision(double dt) {
	vector<Entity*> collideObjects;
	map->GetQuadTree()->Clear();
	map->GetQuadTree()->Insert(leftPaddle);
	map->GetQuadTree()->Insert(rightPaddle);
	map->GetQuadTree()->Insert(leftScorePaddle);
	map->GetQuadTree()->Insert(rightScorePaddle);

	map->GetQuadTree()->GetAbleCollideEntities(collideObjects, ball);

	Entity::SideCollision side;

	for (size_t i = 0; i < collideObjects.size(); i++) {
		RECT r1 = collideObjects[i]->GetBound();
		RECT r2 = ball->GetBound();
		auto data = CollisionDetector::RectAndRect(r1, r2);
		if (!data.IsCollided)
			continue;
		ball->OnCollision(collideObjects[i], win);
	}
}

void PlayScene::Reset() {
	auto bufferHeight = Graphic::GetInstance()->GetBackBufferHeight();
	auto bufferWidth = Graphic::GetInstance()->GetBackBufferWidth();

	rightPaddle->SetPosition(bufferWidth - 50 - rightPaddle->GetWidth(), (float)bufferHeight / 2);
	leftPaddle->SetPosition(50 + leftPaddle->GetWidth(), (float)bufferHeight / 2);
	leftScorePaddle->SetPosition(leftScorePaddle->GetWidth() / 2, (float)bufferHeight / 2);
	rightScorePaddle->SetPosition(bufferWidth - rightScorePaddle->GetWidth() / 2, (float)bufferHeight / 2);

	ball->SetPosition(bufferWidth / 2, bufferHeight / 2);
	ball->SetRandomVelocity();
	//ball->SetVelocity(D3DXVECTOR2(BALL_SPEED, 0));
}
