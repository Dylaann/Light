#ifndef OPTIONSSCREEN
#define OPTIONSSCREEN

#include "Game.h"
#include "ResourceManager.h"

class Game;

class OptionsScreen {
public:

	OptionsScreen(Game &game);
	~OptionsScreen();
	void render(sf::RenderWindow & window); //draw loop 
	void update(); //update loop

private:

	GUI m_gui;
	GUI m_guiHelp;
	Label *m_title;
	Label *m_helptitle;
	Label *m_controls;
	Label *m_objects;
	Label *m_key;
	Label *m_battery;
	Label *m_door;
	Label *m_crate;
	Label *m_ball;
	Button *m_Back;
	Button *m_optBack;
	Button *m_help;

	Slider *m_volume;
	CheckBox *m_music;

	sf::Sprite controller;
	sf::Texture m_controllerTexture;

	sf::Sprite key;
	sf::Texture m_keyTexture;

	sf::Sprite battery;
	sf::Texture m_batteryTexture;

	sf::Sprite crate;
	sf::Texture m_crateTexture;

	sf::Sprite door;
	sf::Texture m_doorTexture;

	sf::Sprite ball;
	sf::Texture m_ballTexture;

	int m_currentSelect; //index
	Game *m_game; //game object
	std::unique_ptr<ResourceManager> m_manager; //resource manager


	void goMain();
	void mainOptScreen();
	void helpScreen();

	bool help = false;
	bool mainOpt = true;

};
#endif
