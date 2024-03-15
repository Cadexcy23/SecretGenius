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
class Tile {
public:


	struct tile {
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

	static std::vector<tile> tileList;

	struct tileVariant {
		tile* tileType;
		int textureID;
		void draw(int x, int y, int w, int h)
		{
			Artist artist;
			SDL_Texture* tempTex = tileType->textureSet.variant1;
			switch (textureID)
			{
			case 0:
				tempTex = tileType->textureSet.variant1;
				break;
			case 1:
				tempTex = tileType->textureSet.variant2;
				break;
			case 2:
				tempTex = tileType->textureSet.variant3;
				break;
			case 3:
				tempTex = tileType->textureSet.variant4;
				break;
			}
			artist.drawImage(x, y, w, h, tempTex);
		}
	};

	static std::vector<tileVariant> tileVariantList;

};

	/*struct tile {
		std::string name;
		int textureID;
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
		void draw(int x, int y, int w, int h)
		{
			Artist artist;
			SDL_Texture* tempTex = textureSet.variant1;
			switch (textureID)
			{
			case 0:
				tempTex = textureSet.variant1;
				break;
			case 1:
				tempTex = textureSet.variant2;
				break;
			case 2:
				tempTex = textureSet.variant3;
				break;
			case 3:
				tempTex = textureSet.variant4;
				break;
			}
			artist.drawImage(x, y, w, h, tempTex);
		}
	};

	static tile grass;
	static tile dirt;
};*/