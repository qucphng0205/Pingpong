#pragma once
#include <d3d9.h>
#include <d3dx9.h>
class Entity {
protected:

	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void OnSetPosition(D3DXVECTOR3 pos);

	//vi tri tam position x va y
	D3DXVECTOR3 position;

	//phan toc vx, vy
	D3DXVECTOR2 velocity;

	//size cua entity
	float width, height;

public:
	Entity();

	enum SideCollision {
		Left, //0
		Right, //1
		Top, //2
		Bottom, //3
		TopLeft, //4
		TopRight, //5
		BottomLeft, //6
		BottomRight, //7
		NotKnow
	};
	struct CollisionReturn
	{
		bool IsCollided;
		RECT RegionCollision;
	};
	enum EntityTypes
	{
		None, 
		Player
	};

	EntityTypes tag;

	virtual RECT GetBound();

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(D3DXVECTOR2 pos);
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual void AddPosition(D3DXVECTOR3 pos);
	virtual void AddPosition(D3DXVECTOR2 pos);
	virtual void AddPosition(float x, float y);
	virtual D3DXVECTOR3 GetPosition();
	

	virtual void SetWidth(int width);
	virtual int GetWidth();
	virtual void SetHeight(int height);
	virtual int GetHeight();

	virtual void SetVelocity(D3DXVECTOR2 vel);

	virtual float GetVx();
	virtual void SetVx(float vx);
	virtual void AddVx(float vx);

	virtual float GetVy();
	virtual void SetVy(float vy);
	virtual void AddVy(float vy);

	virtual void Update(double dt);

	virtual void OnCollision(Entity *impactor, CollisionReturn data, SideCollision side);

};