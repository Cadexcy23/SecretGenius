#include <SDL_mixer.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Mixer.h"




Mix_Music* sIntroMusic = NULL;
Mix_Chunk* Mixer::sSwordFromSheath = NULL;

bool Mixer::loadSoundSettings()
{
	std::ifstream myFile;
	myFile.open("Resource/settings.TXT");
	if (myFile.is_open())
	{
		//printf("Did load settings for sound \n");

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

			Mix_VolumeMusic(dataI);
			
			counter++;
		}
		if (counter == 2)
		{
			getline(myFile, dataS);
			std::istringstream iss(dataS);
			std::string subS;
			iss >> subS;
			dataI = std::stoi(subS);

			Mix_Volume(-1, dataI);
			
			counter++;
		}



		myFile.close();
		return true;
	}
	else
	{
		//printf("Couldn't load settings for sound \n");
		return false;
	}
}

bool Mixer::saveSoundSettings()
{
	std::ofstream myFile;
	myFile.open("Resource/settings.TXT");
	if (myFile.is_open())
	{
		//printf("Did save settings for sound \n");

		myFile << Mix_VolumeMusic(-1);
		
		return true;
	}
	else
	{
		//printf("Couldn't save settings for sound \n");
		return false;
	}
}

bool Mixer::loadSoundMedia()
{
	bool success = true;
	//Load music
	sIntroMusic = Mix_LoadMUS("Resource/sound/music/intro.wav");
	if (sIntroMusic == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	//Load SoundFX
	Mixer::sSwordFromSheath = Mix_LoadWAV("Resource/sound/soundFX/thinSwordDrawFromSheath.wav");
	if (Mixer::sSwordFromSheath == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}


	//Load volume from settings
	loadSoundSettings();
	
	Mix_PlayMusic(sIntroMusic, -1);
	return success;
}