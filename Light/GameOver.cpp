#include "GameOver.h"

GameOver::GameOver(Game & game) :
	m_game(&game)
{
	m_title = new Label("Level Complete!", 50, 50);
	m_gui.addLabel(m_title);
	m_play = new Label("Press A to continue", 50, 600);
	m_gui.addLabel(m_play);
	m_title->changeTextSize(200);



	if (!m_buffer.loadFromFile("ASSETS\\SOUNDS\\levelcomplete.wav"))
	{
	}
	m_levelSound.setBuffer(m_buffer);
	m_levelSound.setVolume(70);
}

GameOver::~GameOver()
{
}

void GameOver::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	m_gui.draw(window);
}

void GameOver::update()
{
	m_xbox.update();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || m_xbox.m_currentState.A == true && !m_xbox.m_previousState.A)
	{
		goNextLevel();
	}

	
}

void GameOver::goNextLevel()
{
	if (GameStates::Play && sf::Keyboard::isKeyPressed(sf::Keyboard::A) || m_xbox.m_currentState.A == true && !m_xbox.m_previousState.A)
	{
		if(level1Complete && !level2Complete && !level3Complete)
		{
			m_levelSound.play();
			m_game->changeGameStates(GameStates::level2S);
		}
		else if (level1Complete && level2Complete && !level3Complete)
		{
			m_levelSound.play();
			m_game->changeGameStates(GameStates::level3S);
		}
		else if (level1Complete && level2Complete && level3Complete)
		{
			level1Complete = false;
			level2Complete = false;
			level3Complete = false;
			m_game->changeGameStates(GameStates::CreditsScreen);
		}

	}
	
}