#ifndef GAMEOVER
#define GAMEOVER

#include "Game.h"
#include "XB0XCONTROLLER.h"

class Game;

class GameOver {
public:

	GameOver(Game &game);
	~GameOver();
	void render(sf::RenderWindow & window); //draw loop 
	void update(); //update loop

	bool level1Complete = false;
	bool level2Complete = false;
	bool level3Complete = false;
	
private:

	GUI m_gui;
	Label *m_title;
	Label *m_play;
	sf::SoundBuffer m_buffer;
	sf::Sound m_levelSound;

	Game *m_game; //game object

	void goNextLevel();

	XboxController m_xbox; //xbox controller

};
#endif