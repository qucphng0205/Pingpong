#include "Camera.h"

Camera::Camera(int width, int height) {
	this->width = width;
	this->height = height;
}

void Camera::SetPosition(D3DXVECTOR3 pos) {
	position = pos;
}

D3DXVECTOR3 Camera::GetPosition() {
	return position;
}

int Camera::GetWidth() {
	return width;
}

int Camera::GetHeight() {
	return height;
}

RECT Camera::GetBound() {
	RECT r;
	r.top = position.y - height / 2;
	r.left = position.x - width / 2;
	r.bottom = r.top + height;
	r.right = r.left + width;
	return r;
}

bool Camera::IsContain(RECT r) {
	RECT bound = GetBound();
	if (r.right < bound.left || r.left > bound.right)
		return false;
	if (r.top > bound.bottom || r.bottom < bound.top)
		return false;
	return true;
}

Camera::~Camera() {
}
