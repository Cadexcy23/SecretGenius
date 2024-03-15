#pragma once
#ifndef SDL_mixer
#include <SDL_mixer.h>
#endif

class Mixer {
public:

	bool loadSoundSettings();

	bool saveSoundSettings();

	bool loadSoundMedia();

	static Mix_Chunk* sSwordFromSheath;
};