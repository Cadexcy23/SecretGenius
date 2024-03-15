#pragma once
#ifndef Character
#include "Character.h"
#endif
#ifndef Map
#include "Map.h"
#endif
class Combat {
public:
	static int selectedCharID;
	static std::vector<std::vector<bool>> moveRange;
	static std::vector<std::vector<Map::pos>> movePaths;


	void controlCombat(int input);

	void drawCombat();

};