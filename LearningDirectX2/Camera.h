#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "MyHelper.h"
class Camera {
private:
	D3DXVECTOR3 position;
	int width;
	int height;
public:
	Camera(int width, int height);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition();
	int GetWidth();
	int GetHeight();
	RECT GetBound();
	bool IsContain(RECT r);
	~Camera();
};