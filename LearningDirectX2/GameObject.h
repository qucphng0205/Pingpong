#pragma once
class GameObject {
public:
	float x;
	float y;
	void SetPosition(float x, float y) {
		this->x = x; this->y = y;
	}
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; };
	GameObject(float x, float y) { this->x = x; this->y = y; };
	~GameObject() {};
};