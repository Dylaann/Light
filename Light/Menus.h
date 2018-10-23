#pragma once
#include<SFML\Graphics.hpp>
#include<functional>
#include "Game.h"

class Game;

class Menus {

public:
	Menus(Game &game) { setupGui(); };

	virtual void  update(); //update

	void draw(sf::RenderWindow &window)
	{
		m_gui.draw(window);
	}; //draw

	void setupFont() 
	{
		if (!m_font.loadFromFile("ASSETS\\FONTS\\PAPYRUS.ttf"))
		{
			std::cout << "problem loading arial black font" << std::endl;
		}
	};

	virtual void setupGui() = 0;

protected:
	sf::Font m_font; // font used by message
	GUI m_gui; //gui
};

class MainMenu : public Menus {

	MainMenu(Menus const& m, Game &game) : Menus(m), m_game(&game) {};
	void setupGui() override;
private:
	bool active = false;
	int m_currentSelect = 0;

	//widgets
	static const int MAX_ITEMS = 3;
	Widget* m_widgets[MAX_ITEMS];
	Label* m_title;
	Button* m_Play;
	Button* m_Options;
	Button* m_Quit;

	void goPlay();
	void quit();
	void goOptions();

	Game *m_game;

};

void MainMenu::setupGui()
{
	m_title = new Label("Light", 180, 50);
	m_gui.addLabel(m_title);
	m_Play = new Button("Play", 300, 250);
	m_Play->getFocus();
	m_Play->Enter = std::bind(&MainMenu::goPlay, this);
	m_Options = new Button("Options", 300, 450);
	m_Options->Enter = std::bind(&MainMenu::goOptions, this);
	m_Quit = new Button("Quit", 300, 650);
	m_Quit->Enter = std::bind(&MainMenu::quit, this);
	m_gui.addButton(m_Play);
	m_gui.addButton(m_Options);
	m_gui.addButton(m_Quit);

	m_currentSelect = 0;
	m_gui.vertical = true;
	m_title->changeTextSize(100);
}

void MainMenu::goPlay()
{
	m_game->changeGameStates(GameStates::Play);
}

void MainMenu::quit()
{
	m_game->m_window.close();
}

void MainMenu::goOptions()
{
	m_game->changeGameStates(GameStates::Options);
}
