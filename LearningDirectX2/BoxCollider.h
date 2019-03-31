#pragma once
class BoxCollider {
private:
	float width, height;
	float velX, velY;
public:
	void SetWidth(float width) { this->width = width; }
	void SetHeight(float height) { this->height = height; }
	void SetVelocity(float x, float y) { this->velX = x; this->velY = y; }
	float GetVelocityX() { return velX; }
	float GetVelocityY() { return velY; }
	void FlipVelX();
	void FlipVelY();
};