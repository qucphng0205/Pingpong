#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Graphic {
protected:
	static Graphic *instance;
	HWND hWnd;

	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddv = NULL;

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;

	int bufferWidth;
	int bufferHeight;

public:
	//Ham khoi tao
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT r, int alpha);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture);
	LPDIRECT3DDEVICE9 GetDirect3DDevice() {
		return d3ddv;
	}
	LPDIRECT3DSURFACE9 GetBackBuffer() {
		return backBuffer;
	}
	LPD3DXSPRITE GetSpriteHandler() {
		return spriteHandler;
	}
	int GetBackBufferWidth() { return bufferWidth; }
	int GetBackBufferHeight() {return bufferHeight; }
	HWND getHWND() { return hWnd; }
	static Graphic *GetInstance();
	~Graphic();
};