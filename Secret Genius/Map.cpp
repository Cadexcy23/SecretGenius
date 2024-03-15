#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include "Map.h"
#include "Tile.h"
#include "Artist.h"
#include "Menus.h"
#include "Object.h"
#include "Character.h"
#include "Controller.h"
#include "Combat.h"

//maybe remove
int mapSizeX = 10, mapSizeY = 10;
int Map::cameraPosX = 0, Map::cameraPosY = 0;
float Map::cameraZoom = 1;



//The maps tiles
std::vector<std::vector<Tile::tileVariant*>> Map::currentMapTiles;
//the maps objects
std::vector<std::vector<Object::objectVariant*>> Map::currentMapObjects;

Map::pos Map::getGridPosUnderMouse()
{
	Map::pos returnPos;

	int scale = 60 * cameraZoom;

	returnPos.x = (Controller::mouseX + cameraPosX) / scale;
	returnPos.y = (Controller::mouseY + cameraPosY) / scale;

	return returnPos;
}

Character::character Map::getCharUnderMouse()
{
	

	for (int a = 0; Character::currentTeam.size() > a; a++)
	{
		if (Character::currentTeam[a].x == getGridPosUnderMouse().x && Character::currentTeam[a].y == getGridPosUnderMouse().y)
		{
			return Character::currentTeam[a];
		}
	}

	return Character::none;
}

Tile::tile Map::getTileUnderMouse()
{
	if (getGridPosUnderMouse().x >= 0 && getGridPosUnderMouse().x < mapSizeX && getGridPosUnderMouse().y >= 0 && getGridPosUnderMouse().y < mapSizeY)
		return *currentMapTiles[getGridPosUnderMouse().x][getGridPosUnderMouse().y]->tileType;

	return Tile::tileList[0];
}

Tile::tileVariant Map::getTileVariantUnderMouse()
{
	if (getGridPosUnderMouse().x >= 0 && getGridPosUnderMouse().x < mapSizeX && getGridPosUnderMouse().y >= 0 && getGridPosUnderMouse().y < mapSizeY)
	{
		return *currentMapTiles[getGridPosUnderMouse().x][getGridPosUnderMouse().y];
	}
	return Tile::tileVariantList[0];
}

Object::object Map::getObjectUnderMouse()
{
	if (getGridPosUnderMouse().x >= 0 && getGridPosUnderMouse().x < mapSizeX && getGridPosUnderMouse().y >= 0 && getGridPosUnderMouse().y < mapSizeY)
		return *currentMapObjects[getGridPosUnderMouse().x][getGridPosUnderMouse().y]->objectType;

	return Object::objectList[0];
}

Object::objectVariant Map::getObjectVariantUnderMouse()
{
	if (getGridPosUnderMouse().x >= 0 && getGridPosUnderMouse().x < mapSizeX && getGridPosUnderMouse().y >= 0 && getGridPosUnderMouse().y < mapSizeY)
	{
		return *currentMapObjects[getGridPosUnderMouse().x][getGridPosUnderMouse().y];
	}
	return Object::objectVariantList[0];
}

int Map::getCharIDUnderMouse()
{
	for (int a = 0; Character::currentTeam.size() > a; a++)
	{
		if (Character::currentTeam[a].x == getGridPosUnderMouse().x && Character::currentTeam[a].y == getGridPosUnderMouse().y)
		{
			return a;
		}
	}

	return -1;
}

bool Map::isSpaceWalkable(int x, int y)
{
	bool walkable = true;
	if (!currentMapTiles[x][y]->tileType->walkable)
		walkable = false;
	if (!currentMapObjects[x][y]->objectType->walkable)
		walkable = false;
	for (int a = 0; Character::currentTeam.size() > a; a++)
	{
		if (Character::currentTeam[a].x == x && Character::currentTeam[a].y == y)
		{
			walkable = false;
		}
	}
	for (int a = 0; Character::enemyTeam.size() > a; a++)
	{
		if (Character::enemyTeam[a].x == x && Character::enemyTeam[a].y == y)
		{
			walkable = false;
		}
	}
	return walkable;
}

void drawTileSelection()
{
	Artist artist;
	int scale = 60 * Map::cameraZoom;

	int moveOffset = clock() % 1500 / 150;
	if (moveOffset > 5)
	{
		moveOffset = 10 - moveOffset;
	}
	moveOffset = moveOffset * Map::cameraZoom;

	int camOffsetX = Map::cameraPosX % scale;
	int camOffsetY = Map::cameraPosY % scale;

	int xPos = (Controller::mouseX + camOffsetX) / scale * scale;
	int yPos = (Controller::mouseY + camOffsetY) / scale * scale;

	artist.drawImage(xPos - moveOffset - camOffsetX, yPos - moveOffset - camOffsetY, 20 * Map::cameraZoom, 20 * Map::cameraZoom, Artist::gTileHoverPiece);
	artist.drawImage(xPos + 40 * Map::cameraZoom + moveOffset - camOffsetX, yPos - moveOffset - camOffsetY, 20 * Map::cameraZoom, 20 * Map::cameraZoom, Artist::gTileHoverPiece, 0, NULL, SDL_FLIP_HORIZONTAL);
	artist.drawImage(xPos - moveOffset - camOffsetX, yPos + 40 * Map::cameraZoom + moveOffset - camOffsetY, 20 * Map::cameraZoom, 20 * Map::cameraZoom, Artist::gTileHoverPiece, 0, NULL, SDL_FLIP_VERTICAL);
	artist.drawImage(xPos + 40 * Map::cameraZoom + moveOffset - camOffsetX, yPos + 40 * Map::cameraZoom + moveOffset - camOffsetY, 20 * Map::cameraZoom, 20 * Map::cameraZoom, Artist::gTileHoverPiece, 180);
}

void drawCharSelection()
{
	if (Combat::selectedCharID == -1)
		return;

	Artist artist;
	int scale = 60 * Map::cameraZoom;

	int moveOffset = clock() % 1500 / 150;
	if (moveOffset > 5)
	{
		moveOffset = 10 - moveOffset;
	}
	moveOffset = moveOffset * Map::cameraZoom;

	int camOffsetX = Map::cameraPosX % scale;
	int camOffsetY = Map::cameraPosY % scale;

	int xPos = Character::currentTeam[Combat::selectedCharID].x * scale;
	int yPos = Character::currentTeam[Combat::selectedCharID].y * scale;

	SDL_SetTextureColorMod(Artist::gTileHoverPiece, 200, 200, 0);
	artist.drawImage(xPos - moveOffset - Map::cameraPosX, yPos - moveOffset - Map::cameraPosY, 20 * Map::cameraZoom, 20 * Map::cameraZoom, Artist::gTileHoverPiece);
	artist.drawImage(xPos + 40 * Map::cameraZoom + moveOffset - Map::cameraPosX, yPos - moveOffset - Map::cameraPosY, 20 * Map::cameraZoom, 20 * Map::cameraZoom, Artist::gTileHoverPiece, 0, NULL, SDL_FLIP_HORIZONTAL);
	artist.drawImage(xPos - moveOffset - Map::cameraPosX, yPos + 40 * Map::cameraZoom + moveOffset - Map::cameraPosY, 20 * Map::cameraZoom, 20 * Map::cameraZoom, Artist::gTileHoverPiece, 0, NULL, SDL_FLIP_VERTICAL);
	artist.drawImage(xPos + 40 * Map::cameraZoom + moveOffset - Map::cameraPosX, yPos + 40 * Map::cameraZoom + moveOffset - Map::cameraPosY, 20 * Map::cameraZoom, 20 * Map::cameraZoom, Artist::gTileHoverPiece, 180);
	SDL_SetTextureColorMod(Artist::gTileHoverPiece, Artist::tileSelecterRGB.r, Artist::tileSelecterRGB.g, Artist::tileSelecterRGB.b);
}

void moveMapWithMouse()
{
	Map::cameraPosX = -1 * (Controller::mouseX - Controller::lastMousePos.x) + Map::cameraPosX;
	Map::cameraPosY = -1 * (Controller::mouseY - Controller::lastMousePos.y) + Map::cameraPosY;

	Controller::lastMousePos.x = Controller::mouseX;
	Controller::lastMousePos.y = Controller::mouseY;
}

void drawTiles()
{
	Artist artist;
	
	//make sure we are culling extra tiles
	int maxDistX = 33, maxDistY = 19;
	if (Map::cameraZoom == 2.0)
	{
		maxDistX = 17;
		maxDistY = 10;
	}
	if (Map::cameraZoom == .5)
	{
		maxDistX = 65;
		maxDistY = 37;
	}
	for (int x = 0; x <= maxDistX; x++)
	{
		for (int y = 0; y <= maxDistY; y++)
		{
			int offsetX, offsetY, camOffsetX, camOffsetY;
			offsetX = int (Map::cameraPosX / (60 * Map::cameraZoom)) + x - 1;
			offsetY = int (Map::cameraPosY / (60 * Map::cameraZoom)) + y - 1;
			camOffsetX = Map::cameraPosX % int(60 * Map::cameraZoom);
			camOffsetY = Map::cameraPosY % int(60 * Map::cameraZoom);
			if (offsetX < mapSizeX && offsetX >= 0 && offsetY < mapSizeY && offsetY >= 0)
			{
				Map::currentMapTiles[offsetX][offsetY]->draw(x * (60 * Map::cameraZoom) - camOffsetX - 60 * Map::cameraZoom, y * (60 * Map::cameraZoom) - camOffsetY - 60 * Map::cameraZoom, 60 * Map::cameraZoom, 60 * Map::cameraZoom);

				//was here

				//draw players here and make a class for players, enemys and a general struct for chars holding what team they are on 2
				for (int a = 0; Character::currentTeam.size() > a; a++)
				{
					if (Character::currentTeam[a].x == offsetX && Character::currentTeam[a].y == offsetY)
						Character::currentTeam[a].draw(x * (60 * Map::cameraZoom) - camOffsetX - 5 * Map::cameraZoom - 60 * Map::cameraZoom, y * (60 * Map::cameraZoom) - camOffsetY - 5 * Map::cameraZoom - 60 * Map::cameraZoom, 70 * Map::cameraZoom, 70 * Map::cameraZoom);
				}

				for (int a = 0; Character::enemyTeam.size() > a; a++)
				{
					if (Character::enemyTeam[a].x == offsetX && Character::enemyTeam[a].y == offsetY)
						Character::enemyTeam[a].draw(x * (60 * Map::cameraZoom) - camOffsetX - 5 * Map::cameraZoom - 60 * Map::cameraZoom, y * (60 * Map::cameraZoom) - camOffsetY - 5 * Map::cameraZoom - 60 * Map::cameraZoom, 70 * Map::cameraZoom, 70 * Map::cameraZoom);
				}
				

				Map::currentMapObjects[offsetX][offsetY]->draw(x * (60 * Map::cameraZoom) - camOffsetX - 5 * Map::cameraZoom - 60 * Map::cameraZoom, y * (60 * Map::cameraZoom) - camOffsetY - 5 * Map::cameraZoom - 60 * Map::cameraZoom, 70 * Map::cameraZoom, 70 * Map::cameraZoom);
			}
			else
				artist.drawImage(x * (60 * Map::cameraZoom) - camOffsetX - 60 * Map::cameraZoom, y * (60 * Map::cameraZoom) - camOffsetY - 60 * Map::cameraZoom, 60 * Map::cameraZoom, 60 * Map::cameraZoom, Artist::gTire);

		}
	}

	

	drawTileSelection();
	drawCharSelection();
}

void updateMapSize()
{
	Map::currentMapTiles.resize(mapSizeX);
	for (int i = 0; i < mapSizeX; i++)
		Map::currentMapTiles[i].resize(mapSizeY);

	Map::currentMapObjects.resize(mapSizeX);
	for (int i = 0; i < mapSizeX; i++)
		Map::currentMapObjects[i].resize(mapSizeY);
}

void resetMap()
{
	srand(clock());
	for (int y = 0; y <= mapSizeY - 1; y++)
	{
		for (int x = 0; x <= mapSizeX - 1; x++)
		{
			Map::currentMapTiles[x][y] = &Tile::tileVariantList[0 + rand() % 4];
			Map::currentMapObjects[x][y] = &Object::objectVariantList[0 + rand() % 4];
		}
	}
}

void Map::saveMap()
{
	std::ofstream myFile;
	myFile.open("Resource/maps/map.SGM");
	if (myFile.is_open())
	{
		myFile << 2;
		
		/*int mapSize = Maps.getMapSize();
		myFile << Maps.getPlayerSpawnX() << "\n";
		myFile << Maps.getPlayerSpawnY() << "\n";
		myFile << mapSize << "\n";
		for (int y = 0; y <= mapSize - 1; y++)
		{
			for (int x = 0; x <= mapSize - 1; x++)
			{
				myFile << Maps.getMapTileID(x, y) << " ";
			}
			myFile << "\n";
		}
		for (int y = 0; y <= mapSize - 1; y++)
		{
			for (int x = 0; x <= mapSize - 1; x++)
			{
				myFile << Maps.getMapEntityID(x, y) << " ";
			}
			myFile << "\n";
		}



		printf("Saved!\n");*/
		myFile.close();
	}
	else
	{
		printf("Unable to save File\n");
	}
}

void Map::loadMap(std::string mapName)
{


	std::ifstream myFile;
	myFile.open("Resource/maps/" + mapName + ".SGM");
	//myFile.open("Resource/maps/map.SGM");
	if (myFile.is_open())
	{
		std::string dataS;
		int dataI = 1;
		int counter = 1;


		if (counter == 1)
		{
			getline(myFile, dataS);
			std::istringstream iss(dataS);
			std::string subS;

			iss >> subS;
			dataI = std::stoi(subS);
			mapSizeX = dataI;
			//printf("Map X: %i \n", mapSizeX);

			iss >> subS;
			dataI = std::stoi(subS);
			mapSizeY = dataI;
			//printf("Map Y: %i \n", mapSizeY);

			updateMapSize();
			resetMap();

			counter++;
		}
		if (counter == 2)
		{
			getline(myFile, dataS);
			dataI = std::stoi(dataS);


			Character::currentTeam.resize(dataI);
			//printf("Friendly team size: %i\n", Character::currentTeam.size());


			Character::enemyTeam.resize(dataI);
			//printf("Enemy team size: %i\n", Spawn::friendlySpawns.size());


			counter++;
		}
		if (counter == 3)
		{
			getline(myFile, dataS);
			std::istringstream iss(dataS);
			std::string subS;

			for (int a = 0; a < Character::currentTeam.size(); a++)
			{

				iss >> subS;
				dataI = std::stoi(subS);
				Character::currentTeam[a].x = dataI;
				//printf("Player%i", a);
				//printf("Spawn X: %i ", dataI);

				iss >> subS;
				dataI = std::stoi(subS);
				Character::currentTeam[a].y = dataI;
				//printf("Spawn Y: %i \n", dataI);
			}
			counter++;
		}
		if (counter == 4)
		{
			getline(myFile, dataS);
			std::istringstream iss(dataS);
			std::string subS;

			for (int a = 0; a < Character::enemyTeam.size(); a++)
			{

				iss >> subS;
				dataI = std::stoi(subS);
				Character::enemyTeam[a].x = dataI;
				//printf("Enemy%i", a);
				//printf("Spawn X: %i ", dataI);

				iss >> subS;
				dataI = std::stoi(subS);
				Character::enemyTeam[a].y = dataI;
				//printf("Spawn Y: %i \n", dataI);
			}
			counter++;
		}
		if (counter == 5)
		{
			std::string subS;
			for (int y = 0; y <= mapSizeY - 1; y++)
			{
				getline(myFile, dataS);
				std::istringstream iss(dataS);
				for (int x = 0; x <= mapSizeX - 1; x++)
				{
					iss >> subS;
					int tileType = std::stoi(subS);
					iss >> subS;
					dataI = std::stoi(subS);
					//printf("Type: %i Variant %i \n", tileType, dataI);
					currentMapTiles[x][y] = &Tile::tileVariantList[tileType * 4 + dataI];
				}
			}
			counter++;
		}
		if (counter == 6)
		{
			std::string subS;
			for (int y = 0; y <= mapSizeY - 1; y++)
			{
				getline(myFile, dataS);
				std::istringstream iss(dataS);
				for (int x = 0; x <= mapSizeX - 1; x++)
				{
					iss >> subS;
					int objectType = std::stoi(subS);
					iss >> subS;
					dataI = std::stoi(subS);
					//printf("Type: %i Variant %i \n", tileType, dataI);
					currentMapObjects[x][y] = &Object::objectVariantList[objectType * 4 + dataI];
				}
			}
			counter++;

		};
		myFile.close();
	}
	else
	{
		printf("Unable to open File\n");
	}

}



void Map::controlMap(int input)
{
	switch (Menus::gameState)
	{
	case Menus::GAME_STATE_NONE:
		break;
	case Menus::GAME_STATE_MAIN_MENU:
		break;
	case Menus::GAME_STATE_IN_COMBAT:
		//Left Mouse Click
		if (input == 1)
		{
			switch (Menus::gameIndex)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}

		//Right Mouse Click
		if (input == 2)
		{
			switch (Menus::gameIndex)
			{
			case 0:
				break;
			}
		}

		//Middle Mouse Click
		if (input == 4)
		{
			Controller::lastMousePos.x = Controller::mouseX;
			Controller::lastMousePos.y = Controller::mouseY;
			switch (Menus::gameIndex)
			{
			case 0:
				//printf("MiddleClick");
				
				break;
			}
		}

		//Keyboard Input
		if (input == 3)
		{
			//KEYBOARD
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_A])
			{
				cameraPosX -= 10;
			}
			if (state[SDL_SCANCODE_D])
			{
				cameraPosX += 10;
			}
			if (state[SDL_SCANCODE_W])
			{
				cameraPosY -= 10;
			}
			if (state[SDL_SCANCODE_S])
			{
				cameraPosY += 10;
			}
			if (state[SDL_SCANCODE_Z])
			{
				if (cameraZoom == .5)
				{
					cameraZoom = 2;
				}
				else if (cameraZoom == 2)
				{
					cameraZoom = 1;
				}
				else if (cameraZoom == 1)
				{
					cameraZoom = .5;
				}
			}
			switch (Menus::gameIndex)
			{
			case 0:
				
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}

		//Middle clicke dragged
		if (input == 14)
		{
			moveMapWithMouse();
		}
		break;
	}
}

void Map::drawMap()
{
	switch (Menus::gameState)
	{
	case Menus::GAME_STATE_NONE:
		break;
	case Menus::GAME_STATE_MAIN_MENU:
		break;
	case Menus::GAME_STATE_IN_COMBAT:
		drawTiles();
		break;
	}
}