#pragma once
#include "Entity.h"
#include <cmath>
class CollisionDetector {
public:
	CollisionDetector();
	//kiem tra va cham giua 2 hinh chu nhat
	static Entity::CollisionReturn RectAndRect(RECT rect, RECT rect2);

	static bool IsCollide(RECT rect1, RECT rect2);

	//neu rectagle qua to thi va cham co the bi sai
	static Entity::SideCollision GetSideCollision(Entity *e1, Entity *e2);

	//kiem tra vi tri va cham dua vao vung va cham cua 2 vat the
	static Entity::SideCollision GetSideCollision(Entity *e1, Entity::CollisionReturn data);

	//kiem tra 1 diem co nam trong hinh chu nhat hay khong
	static bool PointAndRectangle(float x, float y, RECT rect);

	//hinh chu nhat va hinh tron
	~CollisionDetector();
};