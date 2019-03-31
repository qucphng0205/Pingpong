#include "QuadTree.h"

bool QuadTree::IsContain(Entity * entity) {
	RECT r = entity->GetBound();
	return IsContain(r);
}

bool QuadTree::IsContain(RECT r) {
	if (r.left >= bound.left && r.right <= bound.right && r.top >= bound.top && r.bottom <= bound.bottom)
		return true;
	return false;
}

void QuadTree::Split() {
	if (nodes != NULL)
		return;
	nodes = new QuadTree*[4];
	auto halfW = width / 2;
	auto halfH = height / 2;
	nodes[0] = new QuadTree(level + 1,
		MyHelper::ToRect(bound.left, bound.left + halfW, bound.top, bound.top + halfH));
	nodes[1] = new QuadTree(level + 1,
		MyHelper::ToRect(bound.left + halfW, bound.right, bound.top, bound.top + halfH));
	nodes[2] = new QuadTree(level + 1,
		MyHelper::ToRect(bound.left, bound.left + halfW, bound.top + halfH, bound.bottom));
	nodes[3] = new QuadTree(level + 1,
		MyHelper::ToRect(bound.left + halfW, bound.right, bound.top + halfW, bound.bottom));
}

QuadTree::QuadTree(int level, RECT bound) {
	this->level = level;
	this->bound = bound;
	width = bound.right - bound.left;
	height = bound.bottom - bound.top;
}

QuadTree::~QuadTree() {
	Clear();
}

void QuadTree::Clear() {
	if (nodes) {
		for (int i = 0; i < 4; i++) 
			if (nodes[i]) {
				nodes[i]->Clear();
				delete nodes[i];
				nodes[i] = nullptr;
			}
		delete[] nodes;
		nodes = nullptr;
	}
	myEntities.clear();
}

void QuadTree::Insert(Entity * entity) {
	if (nodes != NULL) {
		int index = GetIndex(entity->GetBound());
		if (index != -1) 
			nodes[index]->Insert(entity);
		else 
			this->myEntities.push_back(entity);
	}
	else {
		if (level >= QUADTREE_MAXLEVEL) {
			myEntities.push_back(entity);
			return;
		}
		Split();
		Insert(entity);
	}
}

void QuadTree::GetAbleCollideEntities(std::vector<Entity*> &entities, Entity * entity) {
	if (nodes == NULL) {
		for (auto child : myEntities) 
			entities.push_back(child);
		return;
	}

	int index = this->GetIndex(entity->GetBound());
	if (index != -1) {
		for (auto child : myEntities)
			entities.push_back(child);
		nodes[index]->GetAbleCollideEntities(entities, entity);
	}
	else
		GetAllEntity(entities);
}

void QuadTree::GetAllEntity(std::vector<Entity*>& entities) {
	for (auto child : myEntities) 
		entities.push_back(child);
	if (nodes)
		for (int i = 0; i < 4; i++)
			nodes[i]->GetAllEntity(entities);
}

int QuadTree::GetIndex(RECT r) {
	if (!nodes)
		return -1;
	for (int i = 0; i < 4; i++)
		if (nodes[i]->IsContain(r))
			return i;
	return -1;
}
