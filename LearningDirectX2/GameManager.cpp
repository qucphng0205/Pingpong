#include "GameManager.h"

GameManager::GameManager(HWND hWnd) {
	Graphic::GetInstance()->Init(hWnd);
	SceneManager::GetInstance()->CreateScene(new PlayScene());
}

GameManager::~GameManager() {

}

void GameManager::Update(double dt) {
	//neu khong chuyen canh thi update
	/*if (!SceneManager::GetInstance()->isSceneTransitioning())
		SceneManager::GetInstance()->GetCurrentScene()->Update(dt);
	else {
		SceneTransition::GetInstance()->Update();
		SceneManager::GetInstance()->UpdateWithEffect();
	}*/

	SceneManager::GetInstance()->GetCurrentScene()->Update(dt);
	Render();
}

void GameManager::Render() {
	auto device = Graphic::GetInstance()->GetDirect3DDevice();
	auto spriteHandler = Graphic::GetInstance()->GetSpriteHandler();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();
	device->Clear(0, NULL, D3DCLEAR_TARGET, scene->GetBackColor(), 0.0f, 0);
	/*if (!SceneManager::GetInstance()->isSceneTransitioning())
	SceneManager::GetInstance()->GetCurrentScene()->Render();*/
	//RENDER
	{
		device->BeginScene();

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		scene->Render();

		spriteHandler->End();
		device->EndScene();
	}
	device->Present(NULL, NULL, NULL, NULL);
	
}

