#pragma once
#include "KeyBoard.h"
#include <d3d9.h>

class Scene {
public:
	Scene();
	virtual ~Scene() {}
	D3DCOLOR GetBackColor();
	//virtual void LoadContent();
	//virtual void OnKeyUp();
	//virtual void OnKeyDown();
	//virtual void OnMouseDown(float x, float y);
	virtual void OnMouseMove(float x, float y);
	virtual void Render() = 0;
	virtual void Update(double dt) = 0;
private:
	D3DCOLOR backColor;
};