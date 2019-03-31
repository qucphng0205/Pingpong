#pragma once
#include "Sprites.h"
#include "Textures.h"
#include "Camera.h"
#include "QuadTree.h"
#include <iostream>
#include <fstream>

class Tileset {
	int tileWidth;
	int tileHeight;
	int rows;
	int columns;
	unordered_map<int, LPSPRITE> tiles;
public:
	Tileset(int rows, int columns, int tileWidth, int tileHeight);
	void Add(int id, LPSPRITE tile);
	int GetRows();
	int GetColumns();
	int GetTileWidth();
	int GetTileHeight();
	LPSPRITE GetSprite(int id);
};

class GameMap {
public:
	GameMap();
	GameMap(char* tilesetPath, int tileHeight, int tileWidth);
	void SetMapPath(char *mapPath);
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	QuadTree *GetQuadTree();
	void SetCamera(Camera *cam);
	void Draw();

	~GameMap();
private:
	QuadTree *nodes;
	void LoadTileset(char *filePath, int tileWidth, int tileHeight);
	Tileset *tileset;
	LPCSTR mapPath;
	int rows;
	int columns;
	int **mapIDs;
	std::unordered_map<int, LPSPRITE> listTileset;
	Camera *camera;
};