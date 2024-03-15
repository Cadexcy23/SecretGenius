#pragma once
#ifndef string
#include <string>
#endif
#ifndef Artist
#include "Artist.h"
#endif
#ifndef vector
#include <vector>
#endif
#ifndef time
#include <time.h>
#endif
class Classes {
public:
	Artist artist;
	

	struct charClass
	{
		std::string name;
		int classLevel;
		SDL_Texture* icon;
		void drawIcon(int x, int y)
		{
			Artist artist;

			artist.drawImage(x, y, 64, 64, icon);
			int timeChunk = clock() % 3000 / 15;

			switch (classLevel)
			{
			case 0:
				artist.drawImage(x, y, 64, 64, Artist::gLvl1ClassIconBorder);
				break;
			case 1:
				artist.drawImage(x, y, 64, 64, Artist::gLvl2ClassIconBorder);
				break;
			case 2:
				artist.drawImage(x, y, 64, 64, Artist::gLvl3ClassIconBorder);
				break;
			case 3:
				artist.drawImage(x, y, 64, 64, Artist::gLvl4ClassIconBorder);
				
				if (timeChunk < 66)
				{
					artist.drawImage(x, y, 64, 64, Artist::gLvl4ClassIconBorderAnimation[timeChunk]);
				}

				break;
			case 4:
				break;
			}
		}
	};

	void loadClassIcons();
	void loadClassData();


	

	static std::vector<charClass> classList;

	std::string convertNametoTextureName(Classes::charClass classToConvert);
};