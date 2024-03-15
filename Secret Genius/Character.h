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
class Character {
public:
	struct character
	{
		std::string name;
		int x;
		int y;
		int direction;
		int maxHealth;
		int health;
		int movement;
		//class class;
		int level;
		int experience;
		int dexterity;
		int accuracy;
		int strength;
		int speed;
		int constitution;
		int intelligence;
		int skill;
		int luck;
		bool movable;
		//growth stats
		Artist::characterTextureSet textures;
		void draw(int drawX, int drawY, int w, int h)
		{
			Artist artist;
			SDL_Texture* tempTex = textures.down;
			switch (direction)
			{
			case 0:
				tempTex = textures.up;
				break;
			case 1:
				tempTex = textures.down;
				break;
			case 2:
				tempTex = textures.left;
				break;
			case 3:
				tempTex = textures.right;
				break;
			}
			
			artist.drawImage(drawX, drawY, w, h, tempTex);
			
		}
		
	};

	static character none;


	static std::vector<character> currentTeam;
	static std::vector<character> enemyTeam;
	Artist::characterTextureSet loadCharSprites(std::string folderName);
	void loadCharTest();
	bool getGridPosWalkable(int x, int y);
};