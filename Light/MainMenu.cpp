#include "MainMenu.h"

MainMenu::MainMenu(Game & game) :
	m_game(&game)
{
	m_title = new Label("Light", 180, 50);
	m_gui.addLabel(m_title);
	m_Play = new Button("Play", 300, 275);
	m_Play->getFocus();
	m_Play->Enter = std::bind(&MainMenu::goPlay, this);
	m_Options = new Button("Options", 300, 475);						
	m_Options->Enter = std::bind(&MainMenu::goOptions, this);
	m_Credits = new Button("Credits", 300, 675);
	m_Credits->Enter = std::bind(&MainMenu::goCredits, this);
	m_Quit = new Button("Quit", 300, 875);
	m_Quit->Enter = std::bind(&MainMenu::quit, this);
	m_gui.addButton(m_Play);
	m_gui.addButton(m_Options);
	m_gui.addButton(m_Credits);
	m_gui.addButton(m_Quit);

	m_currentSelect = 0;
	m_gui.vertical = true;
	m_title->changeTextSize(150);
}

MainMenu::~MainMenu()
{
}

void MainMenu::render(sf::RenderWindow & window)
{
	m_gui.draw(window);
}

void MainMenu::update()
{
	m_gui.update(m_currentSelect, 4);
}

void MainMenu::goCredits()
{
	m_game->changeGameStates(GameStates::CreditsScreen);
}


void MainMenu::goPlay()
{
	m_game->changeGameStates(GameStates::Play);
}

void MainMenu::quit()
{
	m_game->m_exitGame = true;
}

void MainMenu::goOptions()
{
	m_game->changeGameStates(GameStates::Options);
}
