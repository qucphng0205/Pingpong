#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "Entity.h"
#include "GameConfig.h"
#include "MyHelper.h"

class GridCell {
	//use topleft coordinates
	D3DXVECTOR2 pos;
	RECT rect;
	//nhung vat the nam trong gridcell
	std::vector<Entity*> m_Entities;
public:
	GridCell() { pos = D3DXVECTOR2(0, 0); }
	GridCell(D3DXVECTOR2 position) { pos = position; };
	GridCell(float x, float y) { pos = D3DXVECTOR2(x, y); };
	void SetRect(float width, float height) { rect = MyHelper::ToRect(pos.x, pos.x + width, pos.y, pos.y + height); }
	RECT GetRect() { return rect; }
	//xoa het vat the
	void ClearEntities();
	//day entities trong gridcell vao entities
	void GetEntityTo(std::vector<Entity*> &entities);
	//day entity vao mang entities gridcell
	void PushEntity(Entity *entity);
	~GridCell();
};

class Grid {
	int rows;
	int columns;
	float cellWidth;
	float cellHeight;
	GridCell **cells;
	//kiem tra xem r1 va r2 co chong len nhau
	bool IsOverlap(RECT r1, RECT r2);
public:
	//constructor cua grid dua vao khung cua the gioi, so luong hang, so luong cot
	Grid(RECT r, int rows = GRID_ROWS, int columns = GRID_COLUMNS);
	//Se clear toan bo entities o trong toan bo gridcell
	void Clear();
	//Dua entity vao gridcell nao do de gridcell do dua vao mang entities cua no
	void InsertEntity(Entity *entity);
	//Lay nhung entity co kha nang va cham voi RECT r
	void GetEntityWithRect(std::vector<Entity*> &entities, RECT r);
	~Grid();
};