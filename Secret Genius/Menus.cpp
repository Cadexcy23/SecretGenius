#include <iostream>
#include <time.h>
#include <SDL_mixer.h>
#include "Menus.h"
#include "Controller.h"
#include "Artist.h"
#include "Map.h"
#include "Mixer.h"
#include "Classes.h"




int Menus::gameState = Menus::GAME_STATE_MAIN_MENU;
int Menus::gameIndex = 0;

std::string* stringSlot = NULL;



void drawSliderBar(int x, int y, int amount)
{
	//lowest should be 28
	Artist artist;

	artist.drawImage(x, y, 20, 110, Artist::gSliderBack);
	artist.drawImage(x + 3, y + 130 - amount, 14, 6, Artist::gSliderKnob);
}

void drawMainMenuBackground()
{
	Artist Artist;
	int timeChunk = clock() % 1920 / 1;

	Artist.drawImage(0 - timeChunk, 0, 1920, 1080, Artist::gBackground);
	Artist.drawImage(0 - timeChunk + 1920, 0, 1920, 1080, Artist::gBackground);

	//Artist.drawImage(1500, 900, 300, 150, Artist::gVan);
	//Artist.drawImage(200, 900, 300, 150, Artist::gPolice);

}

void drawTire(int x, int y)
{
	Artist Artist;
	
	double rotation = clock() % 360 / 1;

	

	Artist.drawImage(x, y, 30, 30, Artist::gTire, rotation);
}

void controlStartNewGameMenu(int input)
{
	Map map;
	Character character;

	//Left Mouse Click
	if (input == 1)
	{
		//Exit Button
		if (Controller::mouseX >= 10 && Controller::mouseX <= 110 && Controller::mouseY >= 970 && Controller::mouseY <= 1070)
		{
			delete stringSlot;
			Menus::gameIndex = 0;
		}
		if (Controller::mouseX >= 1340 && Controller::mouseX <= 1540 && Controller::mouseY >= 960 && Controller::mouseY <= 1060)
		{
			delete stringSlot;
			Menus::gameState = Menus::GAME_STATE_IN_COMBAT;
			Menus::gameIndex = 0;
			map.loadMap("map1");
			character.loadCharTest();
		}
	}

	//Keyboard Input
	if (input == 3)
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		/*//backspace
		if (state[SDL_SCANCODE_BACKSPACE])
		{
			if (stringSlot->length() > 0)
				stringSlot->pop_back();
		}
		if (stringSlot->length() < 22)
		{
			//Space
			if (state[SDL_SCANCODE_SPACE])
			{
				stringSlot->append(" ");
			}
			//Lower Case
			if (!state[SDL_SCANCODE_LSHIFT] && !state[SDL_SCANCODE_RSHIFT])
			{
				if (state[SDL_SCANCODE_A])
				{
					stringSlot->append("a");
				}
				if (state[SDL_SCANCODE_B])
				{
					stringSlot->append("b");
				}
				if (state[SDL_SCANCODE_C])
				{
					stringSlot->append("c");
				}
				if (state[SDL_SCANCODE_D])
				{
					stringSlot->append("d");
				}
				if (state[SDL_SCANCODE_E])
				{
					stringSlot->append("e");
				}
				if (state[SDL_SCANCODE_F])
				{
					stringSlot->append("f");
				}
				if (state[SDL_SCANCODE_G])
				{
					stringSlot->append("g");
				}
				if (state[SDL_SCANCODE_H])
				{
					stringSlot->append("h");
				}
				if (state[SDL_SCANCODE_I])
				{
					stringSlot->append("i");
				}
				if (state[SDL_SCANCODE_J])
				{
					stringSlot->append("j");
				}
				if (state[SDL_SCANCODE_K])
				{
					stringSlot->append("k");
				}
				if (state[SDL_SCANCODE_L])
				{
					stringSlot->append("l");
				}
				if (state[SDL_SCANCODE_M])
				{
					stringSlot->append("m");
				}
				if (state[SDL_SCANCODE_N])
				{
					stringSlot->append("n");
				}
				if (state[SDL_SCANCODE_O])
				{
					stringSlot->append("o");
				}
				if (state[SDL_SCANCODE_P])
				{
					stringSlot->append("p");
				}
				if (state[SDL_SCANCODE_Q])
				{
					stringSlot->append("q");
				}
				if (state[SDL_SCANCODE_R])
				{
					stringSlot->append("r");
				}
				if (state[SDL_SCANCODE_S])
				{
					stringSlot->append("s");
				}
				if (state[SDL_SCANCODE_T])
				{
					stringSlot->append("t");
				}
				if (state[SDL_SCANCODE_U])
				{
					stringSlot->append("u");
				}
				if (state[SDL_SCANCODE_V])
				{
					stringSlot->append("v");
				}
				if (state[SDL_SCANCODE_W])
				{
					stringSlot->append("w");
				}
				if (state[SDL_SCANCODE_X])
				{
					stringSlot->append("x");
				}
				if (state[SDL_SCANCODE_Y])
				{
					stringSlot->append("y");
				}
				if (state[SDL_SCANCODE_Z])
				{
					stringSlot->append("z");
				}
			}
			//Capital
			if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT])
			{
				if (state[SDL_SCANCODE_A])
				{
					stringSlot->append("A");
				}
				if (state[SDL_SCANCODE_B])
				{
					stringSlot->append("B");
				}
				if (state[SDL_SCANCODE_C])
				{
					stringSlot->append("C");
				}
				if (state[SDL_SCANCODE_D])
				{
					stringSlot->append("D");
				}
				if (state[SDL_SCANCODE_E])
				{
					stringSlot->append("E");
				}
				if (state[SDL_SCANCODE_F])
				{
					stringSlot->append("F");
				}
				if (state[SDL_SCANCODE_G])
				{
					stringSlot->append("G");
				}
				if (state[SDL_SCANCODE_H])
				{
					stringSlot->append("H");
				}
				if (state[SDL_SCANCODE_I])
				{
					stringSlot->append("I");
				}
				if (state[SDL_SCANCODE_J])
				{
					stringSlot->append("J");
				}
				if (state[SDL_SCANCODE_K])
				{
					stringSlot->append("K");
				}
				if (state[SDL_SCANCODE_L])
				{
					stringSlot->append("L");
				}
				if (state[SDL_SCANCODE_M])
				{
					stringSlot->append("M");
				}
				if (state[SDL_SCANCODE_N])
				{
					stringSlot->append("N");
				}
				if (state[SDL_SCANCODE_O])
				{
					stringSlot->append("O");
				}
				if (state[SDL_SCANCODE_P])
				{
					stringSlot->append("P");
				}
				if (state[SDL_SCANCODE_Q])
				{
					stringSlot->append("Q");
				}
				if (state[SDL_SCANCODE_R])
				{
					stringSlot->append("R");
				}
				if (state[SDL_SCANCODE_S])
				{
					stringSlot->append("S");
				}
				if (state[SDL_SCANCODE_T])
				{
					stringSlot->append("T");
				}
				if (state[SDL_SCANCODE_U])
				{
					stringSlot->append("U");
				}
				if (state[SDL_SCANCODE_V])
				{
					stringSlot->append("V");
				}
				if (state[SDL_SCANCODE_W])
				{
					stringSlot->append("W");
				}
				if (state[SDL_SCANCODE_X])
				{
					stringSlot->append("X");
				}
				if (state[SDL_SCANCODE_Y])
				{
					stringSlot->append("Y");
				}
				if (state[SDL_SCANCODE_Z])
				{
					stringSlot->append("Z");
				}
			}
		}*/
	}
}

void drawStartNewGameMenu()
{
	Artist artist;

	//enter name text
	artist.drawLetters("Set up your team", 256, 100, Artist::largeFont);

	//name enter box
	//artist.drawImage(251, 195, 1418, 76, Artist::gNameBackplate);
	//artist.drawLetters(stringSlot->c_str(), 256, 200, Artist::largeFont);

	//Start button
	if (Controller::mouseX >= 1340 && Controller::mouseX <= 1540 && Controller::mouseY >= 960 && Controller::mouseY <= 1060)
		SDL_SetTextureColorMod(Artist::gStart, 100, 100, 255);
	else
		SDL_SetTextureColorMod(Artist::gStart, 255, 255, 255);
	artist.drawImage(1340, 960, 200, 100, Artist::gStart);
	drawTire(1360, 1030);
	drawTire(1490, 1030);

	//TEMP
	for (int i = 0; i < Classes::classList.size(); i++)
	{
		//Classes::classList[i].drawIcon(64*i, 0);
	}
	
}

void controlMainMenu(int input)
{
	Controller controller;
	Artist artist;
	Map map;
	Mixer mixer;
	Character character;

	switch (Menus::gameIndex)
	{
	case 2:
		controlStartNewGameMenu(input);
		break;
	}

	//Left Mouse Click
	if (input == 1)
	{
		switch (Menus::gameIndex)
		{
		case 0:
			//Exit Button
			if (Controller::mouseX >= 10 && Controller::mouseX <= 110 && Controller::mouseY >= 970 && Controller::mouseY <= 1070)
				Controller::quit = true;

			//Load Button
			if (Controller::mouseX >= 380 && Controller::mouseX <= 580 && Controller::mouseY >= 960 && Controller::mouseY <= 1060)
				Menus::gameIndex = 1;

			//New Button
			if (Controller::mouseX >= 860 && Controller::mouseX <= 1060 && Controller::mouseY >= 960 && Controller::mouseY <= 1060)
			{
				Menus::gameIndex = 2;
				stringSlot = new std::string;
				//std::string tempName = "Caden";
				//*stringSlot = tempName;
			}

			//Options Button
			if (Controller::mouseX >= 1340 && Controller::mouseX <= 1540 && Controller::mouseY >= 960 && Controller::mouseY <= 1060)
				Menus::gameIndex = 3;
			break;
		case 1:
			//Exit Button
			if (Controller::mouseX >= 10 && Controller::mouseX <= 110 && Controller::mouseY >= 970 && Controller::mouseY <= 1070)
				Menus::gameIndex = 0;
			break;
		case 2:
			
			break;
		case 3:
			//Exit Button
			if (Controller::mouseX >= 10 && Controller::mouseX <= 110 && Controller::mouseY >= 970 && Controller::mouseY <= 1070)
			{
				mixer.saveSoundSettings();
				Menus::gameIndex = 0;
			}

			//music volume mute button
			if (Controller::mouseX >= 1820 && Controller::mouseX <= 1900 && Controller::mouseY >= 20 && Controller::mouseY <= 100)
			{
				if (Mix_VolumeMusic(-1) != 0)
				{
					Mix_VolumeMusic(0);
				}
				else
				{
					Mix_VolumeMusic(28);
				}
			}

			//music volume slider
			if (Controller::mouseX >= 1800 && Controller::mouseX <= 1820 && Controller::mouseY >= 20 && Controller::mouseY <= 130)
			{
				int setVolume = 153 - Controller::mouseY;

				Mix_VolumeMusic(setVolume);
			}

			//SoundFX volume mute button
			if (Controller::mouseX >= 1820 && Controller::mouseX <= 1900 && Controller::mouseY >= 140 && Controller::mouseY <= 220)
			{
				if (Mix_Volume(-1, -1) != 0)
				{
					Mix_Volume(-1, 0);
				}
				else
				{
					Mix_Volume(-1, 28);
				}
			}

			//volume slider SoundFX
			if (Controller::mouseX >= 1800 && Controller::mouseX <= 1820 && Controller::mouseY >= 140 && Controller::mouseY <= 250)
			{
				int setVolume = 273 - Controller::mouseY;

				Mix_Volume(-1, setVolume);

			}

			//shitty sword soundFX test
			if (Controller::mouseX >= 1700 && Controller::mouseX <= 1780 && Controller::mouseY >= 140 && Controller::mouseY <= 220)
			{
				Mix_PlayChannel(-1, Mixer::sSwordFromSheath, 0);
			}
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
			break;
		case 1:
			break;
		case 2:
			
			break;
		case 3:
			if (state[SDL_SCANCODE_UP])
			{
				Mix_VolumeMusic(Mix_VolumeMusic(-1) + 1);
			}
			if (state[SDL_SCANCODE_DOWN])
			{
				if (Mix_VolumeMusic(-1) > 28)
					Mix_VolumeMusic(Mix_VolumeMusic(-1) - 1);
			}
			break;
		}
	}

	//Left clicke dragged
	if (input == 11)
	{
		switch (Menus::gameIndex)
		{
		case 3:
			//volume slider Music
			if (Controller::mouseX >= 1800 && Controller::mouseX <= 1820 && Controller::mouseY >= 20 && Controller::mouseY <= 130)
			{
				//this number   \/ is the starting Y + 133
				int setVolume = 153 - Controller::mouseY;

				Mix_VolumeMusic(setVolume);
				
			}

			//volume slider SoundFX
			if (Controller::mouseX >= 1800 && Controller::mouseX <= 1820 && Controller::mouseY >= 140 && Controller::mouseY <= 250)
			{
				int setVolume = 273 - Controller::mouseY;

				Mix_Volume(-1, setVolume);

			}
			break;
		};
	}
	
}

void drawMainMenu()
{
	Artist artist;
	int timeChunk = 0;

	drawMainMenuBackground();

	//Exit button
	if (Controller::mouseX >= 10 && Controller::mouseX <= 110 && Controller::mouseY >= 970 && Controller::mouseY <= 1070)
	{
		timeChunk = clock() % 2000 / 50;
		double rotation;
		switch (timeChunk)
		{
		case 0:
			rotation = 0.0;
			break;
		case 1:
			rotation = 1.0;
			break;
		case 2:
			rotation = 2.0;
			break;
		case 3:
			rotation = 3.0;
			break;
		case 4:
			rotation = 4.0;
			break;
		case 5:
			rotation = 5.0;
			break;
		case 6:
			rotation = 6.0;
			break;
		case 7:
			rotation = 7.0;
			break;
		case 8:
			rotation = 8.0;
			break;
		case 9:
			rotation = 9.0;
			break;
		case 10:
			rotation = 10.0;
			break;
		case 11:
			rotation = 9.0;
			break;
		case 12:
			rotation = 8.0;
			break;
		case 13:
			rotation = 7.0;
			break;
		case 14:
			rotation = 6.0;
			break;
		case 15:
			rotation = 5.0;
			break;
		case 16:
			rotation = 4.0;
			break;
		case 17:
			rotation = 3.0;
			break;
		case 18:
			rotation = 2.0;
			break;
		case 19:
			rotation = 1.0;
			break;
		case 20:
			rotation = 0.0;
			break;
		case 21:
			rotation = -1.0;
			break;
		case 22:
			rotation = -2.0;
			break;
		case 23:
			rotation = -3.0;
			break;
		case 24:
			rotation = -4.0;
			break;
		case 25:
			rotation = -5.0;
			break;
		case 26:
			rotation = -6.0;
			break;
		case 27:
			rotation = -7.0;
			break;
		case 28:
			rotation = -8.0;
			break;
		case 29:
			rotation = -9.0;
			break;
		case 30:
			rotation = -10.0;
			break;
		case 31:
			rotation = -9.0;
			break;
		case 32:
			rotation = -8.0;
			break;
		case 33:
			rotation = -7.0;
			break;
		case 34:
			rotation = -6.0;
			break;
		case 35:
			rotation = -5.0;
			break;
		case 36:
			rotation = -4.0;
			break;
		case 37:
			rotation = -3.0;
			break;
		case 38:
			rotation = -2.0;
			break;
		case 39:
			rotation = -1.0;
			break;
		}
		artist.drawImage(10, 970, 100, 100, Artist::gExit, rotation);
	}
	else
	{
		artist.drawImage(10, 970, 100, 100, Artist::gExit);
	}

	switch (Menus::gameIndex)
	{
	case 0:
		artist.drawLetters("Secret Genius", 100, 100, Artist::largeFont);
		//Load Button
		if (Controller::mouseX >= 380 && Controller::mouseX <= 580 && Controller::mouseY >= 960 && Controller::mouseY <= 1060)
			SDL_SetTextureColorMod(Artist::gLoad, 255, 100, 100);
		else
			SDL_SetTextureColorMod(Artist::gLoad, 255, 255, 255);
		artist.drawImage(380, 960, 200, 100, Artist::gLoad);
		drawTire(400, 1030);
		drawTire(530, 1030);

		//New Button
		if (Controller::mouseX >= 860 && Controller::mouseX <= 1060 && Controller::mouseY >= 960 && Controller::mouseY <= 1060)
			SDL_SetTextureColorMod(Artist::gNew, 100, 255, 100);
		else
			SDL_SetTextureColorMod(Artist::gNew, 255, 255, 255);
		artist.drawImage(860, 960, 200, 100, Artist::gNew);
		drawTire(880, 1030);
		drawTire(1010, 1030);

		//Options Button
		if (Controller::mouseX >= 1340 && Controller::mouseX <= 1540 && Controller::mouseY >= 960 && Controller::mouseY <= 1060)
			SDL_SetTextureColorMod(Artist::gOptions, 100, 100, 255);
		else
			SDL_SetTextureColorMod(Artist::gOptions, 255, 255, 255);
		artist.drawImage(1340, 960, 200, 100, Artist::gOptions);
		drawTire(1360, 1030);
		drawTire(1490, 1030);
		break;
	case 1:
		break;
	case 2:
		drawStartNewGameMenu();
		break;
	case 3:
		//Music Volume
		if (Controller::mouseX >= 1820 && Controller::mouseX <= 1900 && Controller::mouseY >= 20 && Controller::mouseY <= 100)
		{
			SDL_SetTextureColorMod(Artist::gVolumeIcon, 225, 225, 0);
		}
		else
		{
			SDL_SetTextureColorMod(Artist::gVolumeIcon, 255, 255, 255);
		}
		artist.drawImage(1820, 20, 80, 80, Artist::gVolumeIcon);
		if (Mix_VolumeMusic(-1) == 0)
			artist.drawImage(1820, 20, 80, 80, Artist::gVolumeCrossout);

		if (Mix_VolumeMusic(-1) < 28)
			drawSliderBar(1800, 20, 28);
		else
			drawSliderBar(1800, 20, Mix_VolumeMusic(-1));

		//SoundFX Volume
		if (Controller::mouseX >= 1820 && Controller::mouseX <= 1900 && Controller::mouseY >= 140 && Controller::mouseY <= 220)
		{
			SDL_SetTextureColorMod(Artist::gVolumeIcon, 225, 225, 0);
		}
		else
		{
			SDL_SetTextureColorMod(Artist::gVolumeIcon, 255, 255, 255);
		}
		artist.drawImage(1820, 140, 80, 80, Artist::gVolumeIcon);
		if (Mix_Volume(-1, -1) == 0)
			artist.drawImage(1820, 140, 80, 80, Artist::gVolumeCrossout);

		if (Mix_Volume(-1, -1) < 28)
			drawSliderBar(1800, 140, 28);
		else
			drawSliderBar(1800, 140, Mix_Volume(-1, -1));

		//shitty sword soundFX test
		artist.drawImage(1700, 140, 80, 80, Artist::gShittySword);

		break;
	};
}





void Menus::drawMenus()
{
	//TEMP
	//printf("GameState: %i \n GameIndex: %i \n", Menus::gameState, Menus::gameIndex);
	switch (Menus::gameState)
	{
	case 0:
		break;
	case Menus::GAME_STATE_MAIN_MENU:
		drawMainMenu();
		break;
	}
}

void Menus::controlMenus(int input)
{
	switch (Menus::gameState)
	{
	case Menus::GAME_STATE_MAIN_MENU:
		controlMainMenu(input);
		break;
	}
}