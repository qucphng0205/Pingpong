#pragma once
#include <d3d9.h>
#include "Entity.h"
#include <vector>
#include "GameConfig.h"
#include "MyHelper.h"

class QuadTree {
protected:
	int level;
	int height;
	int width;
	RECT bound;
	QuadTree** nodes;
	std::vector<Entity*> myEntities;
	bool IsContain(Entity *entity);
	bool IsContain(RECT r);
	void Split();
public:
	QuadTree(int level, RECT bound);
	~QuadTree();
	void Clear();
	void Insert(Entity *entity);
	void GetAbleCollideEntities(std::vector<Entity*> &entities, Entity *entity);
	void GetAllEntity(std::vector<Entity*> &entities);
	int GetIndex(RECT bound);
};