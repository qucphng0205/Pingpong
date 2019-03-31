#pragma once
#include <unordered_map>
#include "Sprites.h"
#include <vector>
#include "MyHelper.h"

using namespace std;

class AnimationFrame : public Sprite {
	DWORD time;
public:
	AnimationFrame(LPDIRECT3DTEXTURE9 texture, RECT r, int time = 0.1) : Sprite(r, texture) {
		this->time = time;
	}
	DWORD GetTime() {
		return time;
	}

};
typedef AnimationFrame *LPANIMATION_FRAME;

class Animation {
	DWORD lastFrameTime;
	float defaultTime;
	int currentFrame;
	int totalFrame;
	float currentTotalTime;
	std::vector<LPANIMATION_FRAME> frames;

public:
	Animation(float defaultTime = 0.1);
	void AddFrame(LPANIMATION_FRAME frame);
	void AddFrames(LPDIRECT3DTEXTURE9 texture, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL);
	int GetWidthCurrentFrame();
	int GetHeightCurrentFrame();
	void Render(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void Update(double dt);
};
typedef Animation *LPANIMATION;
