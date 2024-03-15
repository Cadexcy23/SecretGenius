#include "Classes.h"


std::vector<Classes::charClass> Classes::classList;





std::string Classes::convertNametoTextureName(Classes::charClass classToConvert)
{
	std::string convertedName = classToConvert.name;

	for (int i = 0; i < convertedName.length(); i++)
	{
		if (convertedName[i] == 0x20)
		{
			//printf("Found space\n");
			convertedName.erase(i, 1);
		}
	}
	
	//printf("Returned string: %s\n", convertedName.c_str());

	return convertedName;
}

void Classes::loadClassIcons()
{
	Artist artist;

	classList.push_back({ "Thug", 0 });
	classList.push_back({ "Snatcher", 1 });
	classList.push_back({ "Street Ninja", 2 });
	classList.push_back({ "Assassin", 3 });

	for (int i = 0; i < classList.size(); i++)
	{
		classList[i].icon = artist.loadTexture("Resource/classes/" + convertNametoTextureName(classList[i]) + "Icon.png");
		//printf("loaded class %i\n", i);
	}
}

void Classes::loadClassData()
{
	loadClassIcons();
}