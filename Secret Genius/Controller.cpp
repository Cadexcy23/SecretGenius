#include <SDL.h>
#include <stdio.h>
#include "Controller.h"
#include "Menus.h"
#include "Map.h"
#include "Combat.h"

int Controller::mouseX = 0;
int Controller::mouseY = 0;
Map::pos Controller::lastMousePos = { Controller::mouseX, Controller::mouseY };

//Keeps track if game is running
bool Controller::quit = false;
//Event handler
SDL_Event e;



void Controller::controller()
{
	//Set mouse pos
	SDL_GetMouseState(&Controller::mouseX, &Controller::mouseY);
	//printf("Mouse X: %i Mouse Y: %i\n", Controller::mouseX, Controller::mouseY);
	//Declare classes
	Menus menus;
	Map map;
	Combat combat;
	//Handle events on queue
	if (SDL_PollEvent(&e) != 0)
	{
		//printf("input detected: %i\n", e.type);
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			Controller::quit = true;
		}



		//MOUSE
		Uint32 mouseState = SDL_GetMouseState(NULL, NULL);
		//User clicks
		//printf("mouse input: %i \n", mouseState);
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			//printf("mouse input: %i \n", mouseState);
			//LEFT CLICK
			if (mouseState == 1)
			{
				//printf("Mouse X: %i Mouse Y: %i\n", Controller::mouseX, Controller::mouseY);
				menus.controlMenus(1);
				combat.controlCombat(1);
			}

			//RIGHT CLICK
			if (mouseState == 4)
			{
				menus.controlMenus(2);
			}

			//MIDDLE CLICK
			if (mouseState == 2)
			{
				menus.controlMenus(4);
				map.controlMap(4);
			}
		}

		if (e.type == SDL_MOUSEMOTION)
		{
			//LEFT CLICK
			if (mouseState == 1)
			{
				//printf("Dragged left click\n");
				menus.controlMenus(11);
				combat.controlCombat(11);
				map.controlMap(11);
			}

			//RIGHT CLICK
			if (mouseState == 4)
			{
				//printf("Dragged right click\n");
				menus.controlMenus(12);
			}

			//MIDDLE CLICK
			if (mouseState == 2)
			{
				//printf("Dragged middle click\n");
				menus.controlMenus(14);
				map.controlMap(14);
			}
		}


		//Keyboard
		if (e.type == 768)
		{
			menus.controlMenus(3);
			map.controlMap(3);
			combat.controlCombat(3);
		}
		

	}
}