#include "Animation.h"

//ANIMATION FRAME
//ANIMATION
Animation::Animation(float defaultTime) {
	totalFrame = 0;
	currentFrame = 0;
	this->defaultTime = defaultTime;
}

void Animation::AddFrame(LPANIMATION_FRAME frame) {
	frames.push_back(frame);
}

void Animation::AddFrames(LPDIRECT3DTEXTURE9 texture, int rows, int columns, float timePerFrame, D3DCOLOR colorKey) {
	defaultTime = (timePerFrame == 0) ? defaultTime : timePerFrame;
	totalFrame = rows * columns;
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	float frameWidth = (float)desc.Width / columns;
	float frameHeight = (float)desc.Height / rows;
	RECT r = MyHelper::ToRect(0, frameWidth, 0, frameHeight);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			r.left = j * frameHeight;
			r.top = i * frameWidth;
			r.bottom = r.top + frameHeight;
			r.right = r.left + frameWidth;
			AddFrame(new AnimationFrame(texture, r, defaultTime));
		}
}

int Animation::GetWidthCurrentFrame() {
	return frames[currentFrame]->GetWidth();
}

int Animation::GetHeightCurrentFrame() {
	return frames[currentFrame]->GetHeight();
}

void Animation::Render(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey) {
	frames[currentFrame]->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Animation::Update(double dt) {
	if (totalFrame <= 1)
		return;
	int nextFrame = currentFrame + 1;
	if (nextFrame >= totalFrame)
		nextFrame = 0;
	if (currentTotalTime >= frames[nextFrame]->GetTime()) {
		currentTotalTime = 0;
		currentFrame = nextFrame;
	}
	else
		currentTotalTime += dt;
}