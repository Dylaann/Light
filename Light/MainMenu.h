#ifndef MAINMENU
#define MAINMENU

#include "Game.h"

class Game;

class MainMenu {
public:

	MainMenu(Game &game);
	~MainMenu();
	void render(sf::RenderWindow & window); //draw loop 
	void update(); //update loop

private:

	GUI m_gui;
	Label *m_title;
	Button *m_Play;
	Button *m_Options;
	Button *m_Credits;
	Button *m_Quit;

	int m_currentSelect; //index
	Game *m_game; //game object

	void goPlay();
	void quit();
	void goOptions();
	void goCredits();

};
#endif