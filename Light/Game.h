#ifndef GAME
#define GAME

#include <iostream>
#include <SFML/Graphics.hpp>
#include "XB0XCONTROLLER.h"
#include "GUI.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "MainMenu.h"
#include "OptionsScreen.h"
#include "SplashScreen.h"
#include "ResourceManager.h"
#include "Player.h"
#include "GameOver.h"
#include "Pause.h"
#include "Credits.h"

class MainMenu;
class OptionsScreen;
class SplashScreen;
class level1;
class level2;
class level3;
class Player;
class GameOver;
class Pause;
class Credits;

//enums for different gamestates
enum GameStates {
	Splash,
	Play,
	Menu,
	Options, 
	levelComplete,
	level2S,
	level3S,
	PauseScreen,
	CreditsScreen
};


class Game
{
public:
	Game();
	~Game();

	void run();
	void changeGameStates(GameStates gameState); //function to change the screen
	sf::RenderWindow m_window; // main SFML window
	std::unique_ptr<ResourceManager> m_manager; //resource manager
	std::unique_ptr<GameOver>m_gameOver;
	
	sf::Sound music;

	bool m_exitGame = false; // control exiting game

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	GameStates m_currentGameState = GameStates::Splash; //current gamestate/screen

	XboxController m_xbox;
	std::unique_ptr<level1>level;
	std::unique_ptr<level2>level2p;
	std::unique_ptr<level3>level3p;
	std::unique_ptr<MainMenu>m_MainMenu;
	std::unique_ptr<OptionsScreen>m_Options;
	std::unique_ptr<SplashScreen>m_Splash;
	std::unique_ptr<Pause>m_Pause;
	std::unique_ptr<Credits>m_Credits;

	sf::SoundBuffer m_buffer;
	sf::View view;

	sf::Texture loading;
	sf::Texture loading2;
	sf::Texture loading3;
	sf::Sprite loadingSprite;
};

#endif

