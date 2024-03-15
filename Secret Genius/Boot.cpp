#include <stdio.h>
#include "Artist.h"
#include "Controller.h"
#include "Mixer.h"
#include "Classes.h"


int main(int argc, char* args[])
{
	//Declare Artist and controller
	Artist Artist;
	Controller Controller;
	Mixer mixer;
	Classes classes;

	//Start up SDL and create window
	if (!Artist.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!Artist.loadMedia())
		{
			printf("Failed to load media!\n");
		}
		if (!mixer.loadSoundMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//loading setting ect
			classes.loadClassData();
			//Saving.loadMap();


			//While application is running
			while (!Controller::quit)
			{
				//Clear screen
				Artist.clearScreen();




				//Updates game world
				//Logic.update();

				//Draw everything
				Artist.draw();

				//Checks for user input
				Controller.controller();




				//Update screen
				Artist.updateScreen();
			}
		}
	}

	//Free resources and close SDL
	Artist.close();

	return 0;
}