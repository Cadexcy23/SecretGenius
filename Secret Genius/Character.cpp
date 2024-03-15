#include <vector>
#include "Character.h"
#include "Map.h"

struct Character::character
	Character::none {
	"Empty", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

	

std::vector<Character::character> Character::currentTeam;
std::vector<Character::character> Character::enemyTeam;


std::string randNameGen()
{
	std::vector<std::string> nameList = {
		"Caden", "Conner", "Thea", "Cobi", "Sylvera", "Zach", "Landon", "Patrick", "Jacob", "Cooper"
	};

	int randInt = rand() % nameList.size();


	return nameList[randInt];
	
}

std::string randTexNameGen()
{
	std::vector<std::string> nameList = {
		 "flameWizard", "guy", "icecream", "slav"
	};

	int randInt = rand() % nameList.size();


	return nameList[randInt];
}

Artist::characterTextureSet Character::loadCharSprites(std::string folderName)
{
	Artist artist;

	Artist::characterTextureSet tempSet;

	tempSet.up = artist.loadTexture("Resource/charSprites/" + folderName + "/" + folderName + "Up.png");
	tempSet.down = artist.loadTexture("Resource/charSprites/" + folderName + "/" + folderName + "Down.png");
	tempSet.left = artist.loadTexture("Resource/charSprites/" + folderName + "/" + folderName + "Left.png");
	tempSet.right = artist.loadTexture("Resource/charSprites/" + folderName + "/" + folderName + "Right.png");

	return tempSet;
}

Artist::characterTextureSet loadEnemyCharSprites(std::string folderName)
{
	Artist artist;

	Artist::characterTextureSet tempSet;

	tempSet.up = artist.loadTexture("Resource/charSprites/enemys/" + folderName + "/" + folderName + "Up.png");
	tempSet.down = artist.loadTexture("Resource/charSprites/enemys/" + folderName + "/" + folderName + "Down.png");
	tempSet.left = artist.loadTexture("Resource/charSprites/enemys/" + folderName + "/" + folderName + "Left.png");
	tempSet.right = artist.loadTexture("Resource/charSprites/enemys/" + folderName + "/" + folderName + "Right.png");

	return tempSet;
}

void Character::loadCharTest()
{
	Character::character *tempChar;

	for (int i = 0; i < Character::currentTeam.size(); i++)
	{
		tempChar = &Character::currentTeam[i];

		//load in name
		tempChar->name = randNameGen();
		//load in x pos
		tempChar->x = i;
		//load in y pos
		tempChar->y = 0;
		//load in direction ur facing
		tempChar->direction = rand() % 4;
		//load in maxHealth
		tempChar->maxHealth = 10;
		//load in currentHealth
		tempChar->health = 10;
		//load in movment distance
		tempChar->movement = 5;
		//load in class
		//TEMP
		//load in level
		tempChar->level = 100;
		//load in exp
		tempChar->experience = 100000;
		//load in Dex
		tempChar->dexterity = 1;
		//load in ACC
		tempChar->accuracy = 2;
		//load in STR
		tempChar->strength = 3;
		//load in SPEED
		tempChar->speed = 4;
		//load in CON
		tempChar->constitution = 5;
		//load in INT
		tempChar->intelligence = 6;
		//load in SKILL
		tempChar->skill = 7;
		//load in LUCK
		tempChar->luck = 8;
		//load in texture
		tempChar->textures = loadCharSprites(randTexNameGen());
	}

	for (int i = 0; i < Character::enemyTeam.size(); i++)
	{
		tempChar = &Character::enemyTeam[i];

		//load in name
		tempChar->name = randNameGen();
		//load in x pos
		tempChar->x = i;
		//load in y pos
		tempChar->y = 1;
		//load in direction ur facing
		tempChar->direction = 1;
		//load in maxHealth
		tempChar->maxHealth = 10;
		//load in currentHealth
		tempChar->health = 10;
		//load in movment distance
		tempChar->movement = 5;
		//load in class
		//TEMP
		//load in level
		tempChar->level = 100;
		//load in exp
		tempChar->experience = 100000;
		//load in Dex
		tempChar->dexterity = 1;
		//load in ACC
		tempChar->accuracy = 2;
		//load in STR
		tempChar->strength = 3;
		//load in SPEED
		tempChar->speed = 4;
		//load in CON
		tempChar->constitution = 5;
		//load in INT
		tempChar->intelligence = 6;
		//load in SKILL
		tempChar->skill = 7;
		//load in LUCK
		tempChar->luck = 8;
		//load in movable
		tempChar->movable = true;
		//load in texture
		tempChar->textures = loadEnemyCharSprites("enemy1");
	}
	


	
}

bool Character::getGridPosWalkable(int x, int y)
{
	bool returnFlag = true;
	if (x >= 0 && y >= 0)
	{
		if (!Map::currentMapTiles[x][y]->tileType->walkable)
		{
			returnFlag = false;
		}
		else if (!Map::currentMapObjects[x][y]->objectType->walkable)
		{
			returnFlag = false;
		}
	}
	else
	{
		returnFlag = false;
	}

	return returnFlag;
}



