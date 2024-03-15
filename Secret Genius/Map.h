#pragma once
#ifndef string
#include <string>
#endif
#ifndef Character
#include "Character.h"
#endif
#ifndef Tile
#include "Tile.h"
#endif
#ifndef Object
#include "Object.h"
#endif
class Map {
public:

	struct pos {
		int x;
		int y;
	};
	static int cameraPosX, cameraPosY;
	static float cameraZoom;
	static pos lastMousePos;
	static std::vector<std::vector<Tile::tileVariant*>> currentMapTiles;
	static std::vector<std::vector<Object::objectVariant*>> currentMapObjects;

	void loadMap(std::string mapName);
	Map::pos getGridPosUnderMouse();
	Character::character getCharUnderMouse();
	int getCharIDUnderMouse();
	bool isSpaceWalkable(int x, int y);
	Tile::tile getTileUnderMouse();
	Tile::tileVariant getTileVariantUnderMouse();
	Object::object getObjectUnderMouse();
	Object::objectVariant getObjectVariantUnderMouse();
	void saveMap();
	void controlMap(int input);
	void drawMap();

};