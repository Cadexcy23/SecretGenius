#pragma once
#ifndef string
#include <string>
#endif
#ifndef SDL
#include <SDL.h>
#endif // !SDL
#ifndef Artist
#include "Artist.h"
#endif
#ifndef vector
#include <vector>
#endif



class Object {
public:
	struct object {
		std::string name;
		bool walkable;
		int bonusType;
		int bonusAmount;
		Artist::tileTextureSet textureSet;
		void bonus()
		{
			//maybe make and ID that then goes to an external function to figure out what that is
			//Add tile bonus effect here and make it take a player
			//Artist Artist;
			//Artist.drawImage(100, 100, 100, 100, tex);
		}
	};

	static std::vector<object> objectList;

	struct objectVariant {
		object* objectType;
		int textureID;
		void draw(int x, int y, int w, int h)
		{
			Artist artist;
			SDL_Texture* tempTex = objectType->textureSet.variant1;
			switch (textureID)
			{
			case 0:
				tempTex = objectType->textureSet.variant1;
				break;
			case 1:
				tempTex = objectType->textureSet.variant2;
				break;
			case 2:
				tempTex = objectType->textureSet.variant3;
				break;
			case 3:
				tempTex = objectType->textureSet.variant4;
				break;
			}
			artist.drawImage(x, y, w, h, tempTex);
		}
	};

	static std::vector<objectVariant> objectVariantList;

};