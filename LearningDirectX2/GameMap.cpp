#include "GameMap.h"

Tileset::Tileset(int rows, int columns, int tileWidth, int tileHeight) {
	this->rows = rows;
	this->columns = columns;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
}

void Tileset::Add(int id, LPSPRITE tile) {
	tiles[id] = tile;
}

int Tileset::GetRows() {
	return rows;
}

int Tileset::GetColumns() {
	return columns;
}

int Tileset::GetTileWidth() {
	return tileWidth;
}

int Tileset::GetTileHeight() {
	return tileHeight;
}

LPSPRITE Tileset::GetSprite(int id) {
	return tiles[id];
}


GameMap::GameMap() {
	auto bufferWidth = Graphic::GetInstance()->GetBackBufferWidth();
	auto bufferHeight = Graphic::GetInstance()->GetBackBufferHeight();
	grid = new Grid(MyHelper::ToRect(0, bufferWidth, 0, bufferHeight), 1, 1);
}

GameMap::GameMap(char * tilesetPath, int tileWidth, int tileHeight) {
	LoadTileset(tilesetPath, tileWidth, tileHeight);
}

void GameMap::SetMapPath(char * mapPath) {
	this->mapPath = mapPath;
	std::fstream reader(mapPath);
	if (reader.fail()) {
		return;
	}
	reader >> rows;
	reader >> columns;
	mapIDs = new int*[rows];

	for (int i = 0; i < rows; i++) {
		mapIDs[i] = new int[columns];
		for (int j = 0; j < columns; j++) {
			reader >> mapIDs[i][j];
		}
	}
}

int GameMap::GetWidth() {
	return tileset->GetTileWidth() * columns;
}

int GameMap::GetHeight() {
	return tileset->GetTileHeight() * rows;
}

int GameMap::GetTileWidth() {
	return tileset->GetTileWidth();
}

int GameMap::GetTileHeight() {
	return tileset->GetTileHeight();
}

Grid * GameMap::GetGrid() {
	return grid;
}

void GameMap::SetCamera(Camera * cam) {
	camera = cam;
}

void GameMap::Draw() {
	auto heightPos = Graphic::GetInstance()->GetBackBufferHeight() / 2;
	auto widthPos = Graphic::GetInstance()->GetBackBufferWidth() / 2;

	D3DXVECTOR2 trans = D3DXVECTOR2(widthPos - camera->GetPosition().x, heightPos - camera->GetPosition().y);

	for (size_t i = 0; i < 1; i++) {

		//RECT sourceRect;
		//chieu dai va chieu rong cua tile
		int tileWidth = tileset->GetTileWidth();
		int tileHeight = tileset->GetTileHeight();

		for (int m = 0; m < this->rows; m++)
			for (int n = 0; n < this->columns; n++) {
				int id = mapIDs[m][n];
				LPSPRITE sprite = tileset->GetSprite(id);

				RECT spriteBound;
				spriteBound.top = m * tileHeight;
				spriteBound.bottom = spriteBound.top + tileHeight;
				spriteBound.left = n * tileWidth;
				spriteBound.right = spriteBound.left + tileWidth;

				if (camera->IsContain(spriteBound)) {
					D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m*tileHeight + tileHeight / 2, 0);
					sprite->SetHeight(tileHeight);
					sprite->SetWidth(tileWidth);
					sprite->Draw(position, RECT(), D3DXVECTOR2(), trans);
				}
			}
	}

	////xet layer tu tren xuong, tu trai qua phai
	//for (int m = 0; m < ->GetHeight(); m++) {
	//	for (int  n = 0; n < layer->GetWidth(); n++) {
	//		//lay thu tu (index = id) tileset cua tile dang xet
	//		int tilesetIndex = layer->GetTileTilesetIndex(n, m);
	//		if (tilesetIndex == -1)
	//			continue;
	//		//lay tileset cua tile dang xet
	//		const Tmx::Tileset *tileset = map->GetTileset(tilesetIndex);

	//		//Lay so row va column cua tileset
	//		int tilesetWidth = tileset->GetImage()->GetWidth() / tileWidth;
	//		int tilesetHeight = tileset->GetImage()->GetHeight() / tileHeight;

	//		LPSPRITE sprite = listTileset[layer->GetTileTilesetIndex(n, m)];
	//		//Lay id cua tile trong layer
	//		int tileID = layer->GetTileId(n, m);
	//		//Tim vi tri cua tileID trong tileset
	//		int y = tileID / tilesetWidth;
	//		int x = tileID - y * tilesetWidth;
	//		//lay Rect tu tileset
	//		sourceRect.top = y * tileHeight;
	//		sourceRect.bottom = sourceRect.top + tileHeight;
	//		sourceRect.left = x * tileWidth;
	//		sourceRect.right = sourceRect.left + tileWidth;
	//		//ve theo n, m
	//		D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m*tileHeight + tileHeight / 2, 0);
	//		sprite->SetHeight(tileHeight);
	//		sprite->SetWidth(tileWidth);
	//		sprite->Draw(position, sourceRect, D3DXVECTOR2(), trans);
	//	}
	//}
//}
}

GameMap::~GameMap() {
	delete mapIDs;
}

void GameMap::LoadTileset(char * filePath, int tileWidth, int tileHeight) {
	//Parse map tu file 
	Textures::GetInstance()->Add(101, filePath, D3DCOLOR_XRGB(255, 255, 255));
	auto texture = Textures::GetInstance()->Get(101);
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	auto width = desc.Width;
	auto height = desc.Height;
	tileset = new Tileset(height / tileHeight, width / tileWidth, tileWidth, tileHeight);

	for (int i = 0; i < tileset->GetRows(); i++) {
		for (int j = 0; j < tileset->GetColumns(); j++) {
			RECT r;
			r.top = i * tileHeight;
			r.left = j * tileWidth;
			r.bottom = r.top + tileHeight;
			r.right = r.left + tileWidth;
			LPSPRITE sprite = new Sprite(r, texture);
			tileset->Add(i * tileset->GetColumns() + j, sprite);
		}
	}
}

