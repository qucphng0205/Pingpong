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

Entity::SideCollision CollisionDetector::GetSideCollision4(Entity * e1, Entity::CollisionReturn data) {

	float xCenter = data.RegionCollision.left + (data.RegionCollision.right - data.RegionCollision.left) / 2.0f;
	float yCenter = data.RegionCollision.top + (data.RegionCollision.bottom - data.RegionCollision.top) / 2.0f;

	auto e1Width = e1->GetWidth();
	auto e1Height = e1->GetHeight();

	auto xx = sqrt(pow(e1Width / 2, 2) + pow(e1Height / 2, 2));
	auto cornerAngle = (e1Width / 2) / sqrt(pow(e1Width / 2, 2) + pow(e1Height / 2, 2));

	Entity::SideCollision result;
	
	auto pos1 = e1->GetPosition();
	auto pos2 = D3DXVECTOR2(xCenter, yCenter);

	D3DXVECTOR2 direct = D3DXVECTOR2(pos2.x - pos1.x, pos2.y - pos1.y);
	D3DXVec2Normalize(&direct, &direct);
	
	if (abs(abs(direct.x) - abs(cornerAngle)) <= 0.01)
		return Entity::Corner;

	if (direct.y < 0) {
		if (direct.x <= 1 && direct.x > cornerAngle)
			result = Entity::Right;
		else if (direct.x <= cornerAngle && direct.x >= -cornerAngle)
			result = Entity::Top;
		else if (direct.x >= -1 && direct.x < -cornerAngle)
			result = Entity::Left;
	}
	else {
		if (direct.x <= 1 && direct.x > cornerAngle)
			result = Entity::Right;
		else if (direct.x <= 0.707 && direct.x >= -cornerAngle)
			result = Entity::Bottom;
		else if (direct.x >= -1 && direct.x < -cornerAngle)
			result = Entity::Left;
	}
	return result;
}

Entity::SideCollision CollisionDetector::GetSideCollision8(Entity *e1, Entity::CollisionReturn data)
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

float CollisionDetector::SweptAABB(Entity * ent1, Entity * ent2, Entity::SideCollision &side, double dt) {
	RECT r1 = ent1->GetRect();
	RECT r2 = ent2->GetRect();

	if (IsCollide(r1, r2))
		return 1.0;

	auto vel = ent1->GetVelocity() * dt;
	RECT board = GetBoardPhasing(r1, vel.x, vel.y);

	if (!IsCollide(board, r2)) 
		return 1.0;

	float dxEntry = 0, dxExit = 0;
	float dyEntry = 0, dyExit = 0;

	//get min distance of 2 coordinate x and y axis
	if (vel.x > 0) {
		dxEntry = r2.left - r1.right;
		dxExit = r2.right - r1.left;
	}
	else {
		dxEntry = r2.right - r1.left;
		dxExit = r2.left - r1.right;
	}
	if (vel.y > 0) {
		dyEntry = r2.top - r1.bottom;
		dyExit = r2.bottom - r1.top;
	}
	else {
		dyEntry = r2.bottom - r1.top;
		dyExit = r2.top - r1.bottom;
	}

	float txEntry = 0, txExit = 0;
	float tyEntry = 0, tyExit = 0;

	//get time to meet or break up each other in x and y axis
	if (vel.x == 0) {
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else {
		txEntry = dxEntry / vel.x;
		txExit = dxExit / vel.x;
	}
	if (vel.y == 0) {
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else {
		tyEntry = dyEntry / vel.y;
		tyExit = dyExit / vel.y;
	}
	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1 || tyEntry > 1) 
		return 1;
	if (txEntry > tyEntry) {
		if (dxEntry > 0.0f)
			side = Entity::Right;
		else
			side = Entity::Left;
	}
	else {
		if (dyEntry > 0.0f)
			side = Entity::Bottom;
		else
			side = Entity::Top;
	}
	return entryTime;
}

RECT CollisionDetector::GetBoardPhasing(RECT r, float vx, float vy) {
	RECT board = r;
	if (vx > 0)
		board.right += vx;
	else
		board.left += vx;
	if (vy > 0)
		board.bottom += vy;
	else
		board.top += vy;

	return board;
}

bool CollisionDetector::PointAndRectangle(float x, float y, RECT rect) {
	if (x < rect.left || x > rect.right || y < rect.top || y > rect.bottom)
		return false;
	return true;
}

CollisionDetector::~CollisionDetector() {
}
