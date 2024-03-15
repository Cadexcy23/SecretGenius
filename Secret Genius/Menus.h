#pragma once
class Menus {
public:
	enum menuState
	{
		GAME_STATE_NONE,
		GAME_STATE_MAIN_MENU,
		GAME_STATE_IN_COMBAT,
	};
	

	static int gameState;
	static int gameIndex;
	

	void drawMenus();

	void controlMenus(int input);

};