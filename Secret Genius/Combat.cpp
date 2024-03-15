#include <SDL.h>
#include <vector>
#include "Combat.h"
#include "Menus.h"
#include "Character.h"
#include "Artist.h"
#include "Map.h"
#include "Pathfinding.h"
#include "Controller.h"


int Combat::selectedCharID = -1;
std::vector<std::vector<bool>> Combat::moveRange;
std::vector<std::vector<Map::pos>> Combat::movePaths;

std::vector<std::vector<bool>> genMoveRange(Character::character character, std::vector<std::vector<Map::pos>>* path)
{
	Pathfinding pathfinding;
	//printf("gen range started \n");
	//get char info
	int movement = character.movement;
	int x = character.x;
	int y = character.y;

	//make vector holding true and false
	std::vector<std::vector<bool>> returnRange;
	//make vector holding paths
	std::vector<std::vector<Map::pos>> returnPaths;

	//set size to move distance *2 +1 so you can move all directions
	int mapChunkSize = movement * 2 + 1;
	returnRange.resize(mapChunkSize);
	for (int i = 0; i < mapChunkSize; i++)
		returnRange[i].resize(mapChunkSize);

	//set all to true
	for (int y = 0; y <= mapChunkSize - 1; y++)
	{
		for (int x = 0; x <= mapChunkSize - 1; x++)
		{
			returnRange[x][y] = true;
		}
	}

	//check if its walkable start

	//if its in the map
	for (int fory = 0; fory <= mapChunkSize - 1; fory++)
	{
		for (int forx = 0; forx <= mapChunkSize - 1; forx++)
		{
			if (returnRange[forx][fory])
			{
				if (x + forx - movement < 0 || y + fory - movement < 0)
				{
					returnRange[forx][fory] = false;
				}
				if (x + forx - movement >= Map::currentMapTiles.size() || y + fory - movement >= Map::currentMapTiles[0].size())
				{
					returnRange[forx][fory] = false;
				}
			}
		}
	}

	//if its within move distance
	for (int y = 0; y <= mapChunkSize - 1; y++)
	{
		for (int x = 0; x <= mapChunkSize - 1; x++)
		{
			if (returnRange[x][y])
			{
				if (abs(x - movement) + abs(y - movement) > movement)
				{
					returnRange[x][y] = false;
				}
			}
		}
	}

	//if there is something in the way
	for (int forY = 0; forY <= mapChunkSize - 1; forY++)
	{
		for (int forX = 0; forX <= mapChunkSize - 1; forX++)
		{
			if (returnRange[forX][forY])
			{
				//enemies
				for (int i = 0; i < Character::enemyTeam.size(); i++)
				{
					if (Character::enemyTeam[i].x == x + forX - movement && Character::enemyTeam[i].y == y + forY - movement)
					{
						returnRange[forX][forY] = false;
					}
				}
				//tiles
				if (!Map::currentMapTiles[x + forX - movement][y + forY - movement]->tileType->walkable)
				{
					returnRange[forX][forY] = false;
				}
				//objects
				if (!Map::currentMapObjects[x + forX - movement][y + forY - movement]->objectType->walkable)
				{
					returnRange[forX][forY] = false;
				}
			}
		}
	}

	
	//make start point for pathfinder
	Map::pos startPathfinding = { movement, movement };
	//see if you can actualy reach each point using the pathfinder
	returnRange = pathfinding.findPaths(returnRange, startPathfinding, &returnPaths);
	
	//use the table of paths to see if we can make it in the amount of movment we are allowed
	for (int forY = 0; forY <= mapChunkSize - 1; forY++)
	{
		for (int forX = 0; forX <= mapChunkSize - 1; forX++)
		{
			if (returnRange[forX][forY])
			{
				//make path
				std::vector<Map::pos> pathToCheck;
				Map::pos current = { forX, forY };
				while (current.x != movement || current.y != movement)
				{
					pathToCheck.push_back(returnPaths[current.x][current.y]);
					current = returnPaths[current.x][current.y];
				}
				//see if we make it there in movment
				if (pathToCheck.size() > movement)
				{
					returnRange[forX][forY] = false;
				}
			}
		}
	}


	//look for allys at the end
	for (int forY = 0; forY <= mapChunkSize - 1; forY++)
	{
		for (int forX = 0; forX <= mapChunkSize - 1; forX++)
		{
			if (returnRange[forX][forY])
			{
				for (int i = 0; i < Character::currentTeam.size(); i++)
				{
					if (Character::currentTeam[i].x == x + forX - movement && Character::currentTeam[i].y == y + forY - movement)
					{
						returnRange[forX][forY] = false;
					}
				}
			}
		}
	}

	*path = returnPaths;
	return returnRange;
}

void drawMoveRange(Character::character character, std::vector<std::vector<bool>> range)
{
	Artist artist;
	Map map;

	//get info about the current char
	int movement = character.movement;
	int x = character.x;
	int y = character.y;

	//get starting pos to draw from
	int startPosX = x * (60 * Map::cameraZoom) - Map::cameraPosX;
	int startPosY = y * (60 * Map::cameraZoom) - Map::cameraPosY;

	if (range.size() > 0)
	{
		//draw all possible moves as green. REPLACE WITH TEXTURE PROLLY
		artist.changeRenderColor(0, 200, 50, 100);
		for (int y = 0; y <= range.size() - 1; y++)
		{
			for (int x = 0; x <= range.size() - 1; x++)
			{
				if (range[x][y])
				{
					artist.drawRectangle(startPosX + (x - movement) * (60 * Map::cameraZoom), startPosY + (y - movement) * (60 * Map::cameraZoom), 60 * Map::cameraZoom, 60 * Map::cameraZoom);
				}
			}
		}
	}

	//make it draw the path for the spot under mouse assuming reachable
	/*if (Combat::moveRange[map.getGridPosUnderMouse().x + x - movement][map.getGridPosUnderMouse().y + y - movement])
	{
		artist.drawImage(startPosX, startPosY, 60 * Map::cameraZoom, 60 * Map::cameraZoom, Artist::gPathStraight);
	}*/
	//and make it draw attack ranges
}

void drawHUD()
{
	Artist artist;
	Map map;

	//draw move range of selected char
	if (Combat::selectedCharID != -1)
	{
		drawMoveRange(Character::currentTeam[Combat::selectedCharID], Combat::moveRange);
	}
	

	//Top left char/object/tile description
	bool charUnderMouse = false;
	bool objectUnderMouse = false;
	
	for (int a = 0; Character::currentTeam.size() > a; a++)
	{
		if (map.getGridPosUnderMouse().x == Character::currentTeam[a].x && map.getGridPosUnderMouse().y == Character::currentTeam[a].y)
		{
			charUnderMouse = true;
		}
	}
	if (map.getObjectUnderMouse().name != "None")
	{
		objectUnderMouse = true;
	}

	if (objectUnderMouse && charUnderMouse)
	{
		artist.drawImage(60, 60, 360, 216, Artist::gCharObjectInfoBackdrop);
	}
	else if (charUnderMouse)
	{
		artist.drawImage(60, 60, 360, 196, Artist::gCharInfoBackdrop);
	}
	else if (objectUnderMouse)
	{
		artist.drawImage(60, 60, 160, 216, Artist::gObjectInfoBackdrop);
	}
	else
	{
		artist.drawImage(60, 60, 160, 196, Artist::gTileInfoBackdrop);
	}

	map.getTileVariantUnderMouse().draw(80, 80, 120, 120);
	map.getCharUnderMouse().draw(70, 70, 140, 140);
	map.getObjectVariantUnderMouse().draw(70, 70, 140, 140);
	
	artist.drawLetters(map.getTileUnderMouse().name, 65, 202, Artist::smallFont);
	if (objectUnderMouse)
	{
		artist.drawLetters(map.getObjectUnderMouse().name, 65, 224, Artist::smallFont);
	}
	if (charUnderMouse)
	{
		artist.drawLetters(map.getCharUnderMouse().name, 202, 78, Artist::smallFont);
	}

	
}

void Combat::controlCombat(int input)
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
			Map map;
			Combat combat;
			
			if (Combat::selectedCharID == -1)
			{
				Combat::selectedCharID = map.getCharIDUnderMouse();

				if (Combat::selectedCharID != -1)
				{
					moveRange = genMoveRange(Character::currentTeam[Combat::selectedCharID], &movePaths);
				}
			}
			else
			{
				if (map.isSpaceWalkable(map.getGridPosUnderMouse().x, map.getGridPosUnderMouse().y))
				{
					Character::currentTeam[Combat::selectedCharID].x = map.getGridPosUnderMouse().x;
					Character::currentTeam[Combat::selectedCharID].y = map.getGridPosUnderMouse().y;
					Combat::selectedCharID = -1;
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

		//Right Mouse Click
		if (input == 2)
		{
			switch (Menus::gameIndex)
			{
			case 0:
				break;
			}
		}

		//Keyboard Input
		if (input == 3)
		{
			//KEYBOARD
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			switch (Menus::gameIndex)
			{
			case 0:
				if (state[SDL_SCANCODE_ESCAPE])
				{
					Combat::selectedCharID = -1;
				}
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}
		break;
	}
}

void Combat::drawCombat()
{
	switch (Menus::gameState)
	{
	case Menus::GAME_STATE_NONE:
		break;
	case Menus::GAME_STATE_MAIN_MENU:
		break;
	case Menus::GAME_STATE_IN_COMBAT:
		drawHUD();
		
		break;
	}
}