#include <vector>
#include "Pathfinding.h"
#include "Artist.h"
#include "Map.h"


/*void Pathfinding::initPathfinder()
{
	int size = Board::mapSize;
	Map::pos start = Board::startPoint;
	frontier.push_back(start);

	cameFrom.resize(size);
	for (int i = 0; i < size; i++)
		cameFrom[i].resize(size);
	Map::pos invalidPoint = { -1, -1 };
	for (int y = 0; y < cameFrom.size(); y++)
	{
		for (int x = 0; x < cameFrom.size(); x++)
		{
			cameFrom[x][y] = invalidPoint;
		}
	}
	Map::pos initStart = { start.x, start.y };
	cameFrom[start.x][start.y] = initStart;

	visitable.resize(size);
	for (int i = 0; i < size; i++)
		visitable[i].resize(size);
	visitable[start.x][start.y] = true;

	Board::reachableNodes = visitable;

	/*int size = Board::mapSize;
	Map::pos start = Board::startPoint;
	frontier.push_back(start);

	visited.resize(size);
	for (int i = 0; i < size; i++)
		visited[i].resize(size);
	visited[start.x][start.y] = true;

	visitable.resize(size);
	for (int i = 0; i < size; i++)
		visitable[i].resize(size);
	visitable[start.x][start.y] = true;

	Board::reachableNodes = visitable;
}*/


/*void Pathfinding::updatePathfinder()
{
	if (foundGoal)
	{
		return;
	}
	if (frontier.empty())
	{
		return;
	}
	current = frontier.front();
	std::vector<Map::pos> neighbors;
	neighbors = getNeighbors(current, diagToggle);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i].x >= 0 && neighbors[i].x < Board::mapSize && neighbors[i].y >= 0 && neighbors[i].y < Board::mapSize)
		{
			if (cameFrom[neighbors[i].x][neighbors[i].y].x == -1 && cameFrom[neighbors[i].x][neighbors[i].y].y == -1)
			{
				if (Board::mapNodes[neighbors[i].x][neighbors[i].y].walkable)
				{
					frontier.push_back(neighbors[i]);
				}
				cameFrom[neighbors[i].x][neighbors[i].y] = current;
				visitable[neighbors[i].x][neighbors[i].y] = Board::mapNodes[neighbors[i].x][neighbors[i].y].walkable;
				if (neighbors[i].x == Board::goalPoint.x && neighbors[i].y == Board::goalPoint.y)
				{
					foundGoal = true;
				}
			}
		}

	}

	frontier.erase(frontier.begin());
	Board::reachableNodes = visitable;

	if (foundGoal)
	{
		//create path after we found the goal
		current = Board::goalPoint;
		while (current.x != Board::startPoint.x || current.y != Board::startPoint.y)
		{
			path.push_back(cameFrom[current.x][current.y]);
			current = cameFrom[current.x][current.y];
		}


	}

	/*if (foundGoal)
	{
		return;
	}
	if (frontier.empty())
	{
		return;
	}
	current = frontier.front();
	std::vector<Map::pos> neighbors;
	neighbors = getNeighbors(current);
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i].x >= 0 && neighbors[i].x < Board::mapSize && neighbors[i].y >= 0 && neighbors[i].y < Board::mapSize)
		{
			if (!visited[neighbors[i].x][neighbors[i].y])
			{
				if (Board::mapNodes[neighbors[i].x][neighbors[i].y].walkable)
				{
					frontier.push_back(neighbors[i]);
				}
				visited[neighbors[i].x][neighbors[i].y] = true;
				visitable[neighbors[i].x][neighbors[i].y] = Board::mapNodes[neighbors[i].x][neighbors[i].y].walkable;
				if (neighbors[i].x == Board::goalPoint.x && neighbors[i].y == Board::goalPoint.y)
				{
					foundGoal = true;
				}
			}
		}

	}

	frontier.erase(frontier.begin());
	Board::reachableNodes = visitable;
}*/

std::vector<Map::pos> getNeighbors(Map::pos start, bool diag = false)
{
	std::vector<Map::pos> returnNeighbors;

	if (diag)
	{
		returnNeighbors.resize(8);
	}
	else
	{
		returnNeighbors.resize(4);
	}


	//up
	returnNeighbors[0].x = start.x;
	returnNeighbors[0].y = start.y - 1;
	//right
	returnNeighbors[1].x = start.x + 1;
	returnNeighbors[1].y = start.y;
	//down
	returnNeighbors[2].x = start.x;
	returnNeighbors[2].y = start.y + 1;
	//left
	returnNeighbors[3].x = start.x - 1;
	returnNeighbors[3].y = start.y;

	if (diag)
	{
		//up right
		returnNeighbors[4].x = start.x + 1;
		returnNeighbors[4].y = start.y - 1;
		//down right
		returnNeighbors[5].x = start.x + 1;
		returnNeighbors[5].y = start.y + 1;
		//down left
		returnNeighbors[6].x = start.x - 1;
		returnNeighbors[6].y = start.y + 1;
		//up left
		returnNeighbors[7].x = start.x - 1;
		returnNeighbors[7].y = start.y - 1;
	}

	return returnNeighbors;
}

std::vector<std::vector<bool>> Pathfinding::findPaths(std::vector<std::vector<bool>> nodeMap, Map::pos start, std::vector<std::vector<Map::pos>>* paths)
{
	//declare all the variables
	//current frontier point
	Map::pos current;
	//keeps track of moves
	std::vector<Map::pos> frontier;
	//keep track of where we came from
	std::vector<std::vector<Map::pos>> cameFrom;
	//keeptrack of where we can go
	std::vector<std::vector<bool>> visitable;
	//size of node map
	int size = nodeMap.size();
	//list of points next to the one we are on
	std::vector<Map::pos> neighbors;
	//init all the variables
	//start frontier
	frontier.push_back(start);
	//set current 
	current = frontier.front();
	//resize tables
	cameFrom.resize(size);
	for (int i = 0; i < size; i++)
		cameFrom[i].resize(size);
	visitable.resize(size);
	for (int i = 0; i < size; i++)
		visitable[i].resize(size);
	//clear tables and set start point
	Map::pos invalidPos = { -1, -1 };
	for (int y = 0; y < cameFrom.size(); y++)
	{
		for (int x = 0; x < cameFrom.size(); x++)
		{
			cameFrom[x][y] = invalidPos;
		}
	}
	Map::pos initStart = { start.x, start.y };
	cameFrom[start.x][start.y] = initStart;
	visitable[start.x][start.y] = true;
	//init done

	
	//run until frontier is empty
	while(!frontier.empty())
	{
		//get starting points neighbors
		neighbors = getNeighbors(current);
		//go through all neighbors
		for (int i = 0; i < neighbors.size(); i++)
		{
			//make sure it is within the bounds of the node map
			if (neighbors[i].x >= 0 && neighbors[i].x < size && neighbors[i].y >= 0 && neighbors[i].y < size)
			{
				//make sure we havnt visited this neighbor yet
				if (cameFrom[neighbors[i].x][neighbors[i].y].x == -1 && cameFrom[neighbors[i].x][neighbors[i].y].y == -1)
				{
					//add it to the frontier if we can walk on it and add it to the visitable table
					if (nodeMap[neighbors[i].x][neighbors[i].y])
					{
						frontier.push_back(neighbors[i]);
						visitable[neighbors[i].x][neighbors[i].y] = true;
					}
					//add the position we found this neighbor from as the point we got to this one from
					cameFrom[neighbors[i].x][neighbors[i].y] = current;
				}
			}
		}
		//update current and move on to next spot
		current = frontier.front();
		//take the spot we just used off the frontier
		frontier.erase(frontier.begin());
	}






	//return final values
	*paths = cameFrom;
	return visitable;
}

/*void Pathfinding::control(int input)
{
	Pathfinding pathfinding;
	switch (input)
	{
	case 3:
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		//right arrow
		if (state[SDL_SCANCODE_RIGHT])
		{
			pathfinding.updatePathfinder();
		}
		//up arrow
		if (state[SDL_SCANCODE_UP])
		{
			if (toggleOn)
			{
				toggleOn = false;
			}
			else
			{
				toggleOn = true;
			}
		}
		break;
	}
}

void Pathfinding::update()
{
	if (toggleOn)
	{
		Pathfinding::updatePathfinder();
	}
}*/