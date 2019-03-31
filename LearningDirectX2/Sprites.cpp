#include "Sprites.h"
//Sprite

Sprite::Sprite(RECT r, LPDIRECT3DTEXTURE9 tex) {
	texture = tex;
	if (IsRect(r)) {
		width = r.right - r.left;
		height = r.bottom - r.top;
		rect = r;
	}
	else {
		D3DSURFACE_DESC desc;
		texture->GetLevelDesc(0, &desc);
		height = desc.Height;
		width = desc.Width;
		rect = MyHelper::ToRect(0, width, 0, height);
	}
	/*D3DXVECTOR3 m_Position;
	D3DXVECTOR2 m_Scale;
	D3DXVECTOR2 m_Translation;
	float m_Angle;
	D3DXVECTOR2 m_RotationCenter;
	D3DXMATRIX m_Maxtrix;*/
	m_Position = D3DXVECTOR3(0, 0, 0);
	m_Angle = 0;
	m_RotationCenter = D3DXVECTOR2(m_Position.x, m_Position.y);
	m_Scale = D3DXVECTOR2(1, 1);
	m_Translation = D3DXVECTOR2(0, 0);

	spriteHandler = Graphic::GetInstance()->GetSpriteHandler();
}

int Sprite::GetWidth() {
	return width;
}

int Sprite::GetHeight() {
	return height;
}

void Sprite::SetWidth(int width) {
	this->width = width;
}

void Sprite::SetHeight(int height) {
	this->height = height;
}

bool Sprite::IsRect(RECT r) {
	if (r.top == r.bottom)
		return false;
	if (r.left == r.right)
		return false;
	return true;
}

void Sprite::Draw(D3DXVECTOR3 position, RECT r, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey) {

	D3DXVECTOR3 inPosition = m_Position;
	RECT inSourceRect = rect;
	float inRotation = m_Angle;
	D3DXVECTOR2 inScale = m_Scale;
	D3DXVECTOR2 inTranslation = m_Translation;
	D3DXVECTOR2 inRotationCenter = m_RotationCenter;
	D3DXVECTOR2 scalingCenter = D3DXVECTOR2(inPosition.x, inPosition.y);

	if (position != D3DXVECTOR3())
		inPosition = position;

	if (IsRect(r))
		inSourceRect = r;

	if (scale != D3DXVECTOR2())
		inScale = scale;

	if (translation != D3DXVECTOR2())
		inTranslation = translation;

	if (rotationCenter != D3DXVECTOR2())
		inRotationCenter = rotationCenter;
	else
		m_RotationCenter = D3DXVECTOR2(inPosition.x, inPosition.y);

	D3DXMatrixTransformation2D(&m_Maxtrix, &scalingCenter, 0, &inScale, &inRotationCenter,
		inRotation, &inTranslation);
	D3DXMATRIX oldMatrix;
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&m_Maxtrix);

	D3DXVECTOR3 center = D3DXVECTOR3(width / 2, height / 2, 0);
	spriteHandler->Draw(
		texture,
		&inSourceRect,
		&center,
		&inPosition,
		colorKey
	);
	spriteHandler->SetTransform(&oldMatrix);
}