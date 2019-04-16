#include "Grid.h"

void GridCell::ClearEntities() {
	m_Entities.clear();
}

void GridCell::GetEntityTo(std::vector<Entity*> &entities) {
	for (auto child : m_Entities) {
		int childID = child->GetID();
		for (size_t i = 0; i < entities.size(); i++) {
			if (childID == entities[i]->GetID()) {
				childID = -1;
				break;
			}
		}
		if (childID != -1)
			entities.push_back(child);
	}
}

void GridCell::PushEntity(Entity * entity) {
	m_Entities.push_back(entity);
}

GridCell::~GridCell() {
}

bool Grid::IsOverlap(RECT r1, RECT r2) {
	if (r1.bottom < r2.top || r1.top > r2.bottom || r1.left > r2.right || r1.right < r2.left)
		return false;
	return true;
}

Grid::Grid(RECT r, int rows, int columns) {

	cellWidth = (float)(r.right - r.left) / rows;
	cellHeight = (float)(r.bottom - r.top) / columns;

	this->rows = rows;
	this->columns = columns;

	cells = new GridCell*[rows];
	int **a;
	a = new int*[rows];
	for (int i = 0; i < rows; i++) {
		a[i] = new int[columns];
	}
	for (int i = 0; i < rows; i++) {
		cells[i] = new GridCell[columns];
		for (int j = 0; j < columns; j++) {
			cells[i][j] = GridCell(j * cellWidth, i * cellHeight);
			cells[i][j].SetRect(cellWidth, cellHeight);
		}
	}
	cells[0, 0] = cells[0, 0];
}

void Grid::Clear() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			cells[i][j].ClearEntities();
}

void Grid::InsertEntity(Entity * entity) {
	RECT entityBound = entity->GetBound();
	for (int i = 0; i < rows; i++) 
		for (int j = 0; j < columns; j++) 
			if (IsOverlap(cells[i][j].GetRect(), entityBound))
				cells[i][j].PushEntity(entity);
}

void Grid::GetEntityWithRect(std::vector<Entity*> &entities, RECT r) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			RECT rr = cells[i][j].GetRect();
			if (IsOverlap(cells[i][j].GetRect(), r))
				cells[i][j].GetEntityTo(entities);
		}
}

Grid::~Grid() {
	if (cells) {
		for (int i = 0; i < rows; i++) {
			delete[] cells[i];
			cells[i] = nullptr;
		}
	}
	delete[] cells;
	cells = nullptr;
}



