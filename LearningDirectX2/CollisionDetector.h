#pragma once
#include "Entity.h"
#include <cmath>
#include <limits>

class CollisionDetector {
public:
	CollisionDetector();
	//kiem tra va cham giua 2 hinh chu nhat
	static Entity::CollisionReturn RectAndRect(RECT rect, RECT rect2);
	//kiem tra 2 rect co collide
	static bool IsCollide(RECT rect1, RECT rect2);

	//neu rectagle qua to thi va cham co the bi sai
	static Entity::SideCollision GetSideCollision4(Entity *e1, Entity::CollisionReturn data);

	//kiem tra vi tri va cham dua vao vung va cham cua 2 vat the
	static Entity::SideCollision GetSideCollision8(Entity *e1, Entity::CollisionReturn data);
	//
	static float SweptAABB(Entity *ent1, Entity *ent2, Entity::SideCollision &side, double dt = 1/60.0f);
	//board-phasing 
	static RECT GetBoardPhasing(RECT r, float vx, float vy);
	//kiem tra 1 diem co nam trong hinh chu nhat hay khong
	static bool PointAndRectangle(float x, float y, RECT rect);

	//hinh chu nhat va hinh tron
	~CollisionDetector();
};