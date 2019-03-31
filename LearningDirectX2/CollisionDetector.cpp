#include "CollisionDetector.h"

CollisionDetector::CollisionDetector() {

}

Entity::CollisionReturn CollisionDetector::RectAndRect(RECT rect, RECT rect2) {
	Entity::CollisionReturn result;
	if (!IsCollide(rect, rect2)) {
		result.IsCollided = false;
		return result;
	}
	result.IsCollided = true;

	RECT bound;
	bound.top = rect.top > rect2.top ? rect.top : rect2.top;
	bound.left = rect.left > rect2.left ? rect.left : rect2.left;
	bound.right = rect.right < rect2.right ? rect.right : rect2.right;
	bound.bottom = rect.bottom < rect2.bottom ? rect.bottom : rect2.bottom;

	result.RegionCollision = bound;
	return result;
}

bool CollisionDetector::IsCollide(RECT rect1, RECT rect2) {
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
		return false;
	return true;
}

Entity::SideCollision CollisionDetector::GetSideCollision(Entity * e1, Entity * e2) {

	if (!IsCollide(e1->GetBound(), e2->GetBound())) {
		return Entity::NotKnow;
	}

	Entity::SideCollision result;

	float minW = (e1->GetWidth() + e2->GetWidth()) / 2;
	float minH = (e1->GetHeight() + e2->GetHeight()) / 2;

	float tx = (e1->GetPosition().x - e2->GetPosition().x) / minW;
	float ty = (e1->GetPosition().y - e2->GetPosition().y) / minH;

	if (abs(tx) < abs(ty)) {
		if (tx < 0)
			result = Entity::Right;
		else
			result = Entity::Left;
	}

	else {
		if (ty < 0)
			result = Entity::Bottom;
		else
			result = Entity::Top;
	}
}

Entity::SideCollision CollisionDetector::GetSideCollision(Entity *e1, Entity::CollisionReturn data)
{
	float xCenter = data.RegionCollision.left + (data.RegionCollision.right - data.RegionCollision.left) / 2.0f;
	float yCenter = data.RegionCollision.top + (data.RegionCollision.bottom - data.RegionCollision.top) / 2.0f;

	D3DXVECTOR2 cCenter = D3DXVECTOR2(xCenter, yCenter);
	D3DXVECTOR2 eCenter = D3DXVECTOR2(e1->GetPosition());

	//lay vector noi tam Entity va CollisionRect
	D3DXVECTOR2 vec = cCenter - eCenter;

	//chuan hoa vector
	D3DXVec2Normalize(&vec, &vec);

	/*
	- neu vector chuan hoa co y > 0 =>nam phia ben tren Entity
	- neu vector chuan hoa co y < 0 =>nam phia ben duoi Entity
	- neu vector chuan hoa co x > 0 => nam phia ben phai Entity
	- neu vector chuan hoa co x < 0 => nam phia ben trai Entity
	*/

	if (vec.y < 0)
	{
		//va cham phia ben tren
		//lay cos cua goc neu ma nam trong khoang goc 70 -> 110 thi va cham top
		if (vec.x <= 0.35f && vec.x >= -0.35f)
		{
			return Entity::Top;
		}
		else if (vec.x > 0.35f && vec.x < 0.8f)
		{
			//goc trong khoang 35 -> 70 phia ben top - right
			return Entity::TopRight;
		}
		else if (vec.x >= 0.8f)
		{
			return Entity::Right;
		}
		else if (vec.x < -0.35f && vec.x >= -0.8f)
		{
			//va cham phia top - left
			return Entity::TopLeft;
		}
		else
		{
			return Entity::Left;
		}
	}
	else
	{
		//va cham phia ben duoi
		//lay cos cua goc neu ma nam trong khoang goc 70 -> 110 thi va cham top
		if (vec.x <= 0.35f && vec.x >= -0.35)
		{
			return Entity::Bottom;
		}
		else if (vec.x > 0.35 && vec.x < 0.8)
		{
			//goc trong khoang 35 -> 70 phia ben top - right
			return Entity::BottomRight;
		}
		else if (vec.x >= 0.8)
		{
			return Entity::Right;
		}
		else if (vec.x < -0.35f && vec.x > -0.8f)
		{
			//va cham phia top - left
			return Entity::BottomLeft;
		}
		else
		{
			return Entity::Left;
		}
	}

	return Entity::NotKnow;
}

bool CollisionDetector::PointAndRectangle(float x, float y, RECT rect) {
	if (x < rect.left || x > rect.right || y < rect.top || y > rect.bottom)
		return false;
	return true;
}

CollisionDetector::~CollisionDetector() {
}
