#ifndef SPLASHSCREEN
#define SPLASHSCREEN

#include "Game.h"
#include "XB0XCONTROLLER.h"

class Game;

class SplashScreen {
public:

	SplashScreen(Game &game);
	~SplashScreen();
	void render(sf::RenderWindow & window); //draw loop 
	void update(); //update loop

private:

	GUI m_gui;
	Label *m_title;
	Label *m_play;

	Game *m_game; //game object

	void goMain();

	sf::Shader m_shader;
	sf::Sprite m_shaderSprite;
	sf::Texture m_blank;
	float totalTime = 0;

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 30.f);
	XboxController m_xbox; //xbox controller

};
#endif
