#pragma once
#include <unordered_map>
#include <time.h>
#include <Windows.h>
#include <d3dx9.h>
#include "MyHelper.h"
#include "Graphic.h"
using namespace std;

class Sprite {
protected:

	RECT rect;
	LPDIRECT3DTEXTURE9 texture;
	int width, height;

	LPD3DXSPRITE spriteHandler;

	D3DXVECTOR3 m_Position;
	D3DXVECTOR2 m_Scale;
	D3DXVECTOR2 m_Translation;
	float m_Angle;
	D3DXVECTOR2 m_RotationCenter;
	D3DXMATRIX m_Maxtrix;
public:
	Sprite(RECT r, LPDIRECT3DTEXTURE9 tex);
	int GetWidth();
	int GetHeight();
	void SetWidth(int width);
	void SetHeight(int height);
	bool IsRect(RECT r);
	LPDIRECT3DTEXTURE9 GetTexture() { return texture; }
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT r = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 translation = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
};
typedef Sprite *LPSPRITE;