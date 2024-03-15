#pragma once
#ifndef Map
#include "Map.h"
#endif
class Controller {
public:
	static bool quit;
	//Keeps track of mouse Pos
	static int mouseX, mouseY;
	static Map::pos lastMousePos;
	//Checks for inputs from the user
	void controller();
};