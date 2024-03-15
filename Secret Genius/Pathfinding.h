#pragma once
#ifndef vector
#include <vector>
#endif
#ifndef Artist
#include "Artist.h"
#endif
#ifndef Map
#include "Map.h"
#endif
class Pathfinding {
public:
	

	std::vector<std::vector<bool>> findPaths(std::vector<std::vector<bool>> nodeMap, Map::pos start, std::vector<std::vector<Map::pos>>* paths);

};