#ifndef PAUSE
#define PAUSE

#include "Game.h"
#include "XB0XCONTROLLER.h"

class Game;

class Pause {
public:

	Pause(Game &game);
	~Pause();
	void render(sf::RenderWindow & window); //draw loop 
	void update(); //update loop

private:

	void exit();

	GUI m_gui;
	Label *m_title;
	Label *m_play;
	Label *m_quit;

	Game *m_game; //game object

	sf::Shader m_shader;
	sf::Sprite m_shaderSprite;
	sf::Texture m_blank;
	float totalTime = 0;
	sf::SoundBuffer m_buffer;
	sf::Sound m_boxSound;


	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 30.f);
	XboxController m_xbox; //xbox controller

	bool music = false;


};
#endif

