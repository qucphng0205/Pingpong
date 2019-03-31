#pragma once

#include "SceneManager.h"
#include "PlayScene.h"
//#include "SceneTransition.h"
#include "Graphic.h"
//#include "Sound.h"
#define FPS 60;

class GameManager {
public:
	GameManager(HWND hWnd);
	~GameManager();
	void Update(double dt);
	void Render();
};

//class GameManager {
//protected:
//	static GameManager *m_Instance;
//	HWND hWnd;
//
//	LPDIRECT3D9 d3d = NULL;
//	LPDIRECT3DDEVICE9 d3ddv = NULL;
//
//	LPDIRECT3DSURFACE9 backBuffer = NULL;
//	LPD3DXSPRITE spriteHandler = NULL;
//
//public:
//	//Ham khoi tao
//	void Init(HWND hWnd);
//	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
//	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT r, int alpha);
//	LPDIRECT3DDEVICE9 GetDirect3DDevice() {
//		return d3ddv;
//	}
//	LPDIRECT3DSURFACE9 GetBackBuffer() {
//		return backBuffer;
//	}
//	LPD3DXSPRITE GetSpriteHandler() {
//		return spriteHandler;
//	}
//	static GameManager *GetInstance();
//	~GameManager();
//};