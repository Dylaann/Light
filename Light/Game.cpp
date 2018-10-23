#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode(1920, 1080, 32), "Light", sf::Style::Fullscreen}
{
	if (!loading.loadFromFile("ASSETS/IMAGES///loading.jpg"))
	{
	}
	if (!loading2.loadFromFile("ASSETS/IMAGES///loading2.jpg"))
	{
	}
	if (!loading3.loadFromFile("ASSETS/IMAGES///loading3.jpg"))
	{
	}

	loadingSprite.setTexture(loading);
	loadingSprite.setScale(1, 1);

	m_window.draw(loadingSprite);
	m_window.display();

	m_manager = std::make_unique<ResourceManager>();
	loadingSprite.setTexture(loading2);
	m_window.draw(loadingSprite);
	m_window.display();
	level = std::make_unique<level1>(*this);
	loadingSprite.setTexture(loading3);
	m_window.draw(loadingSprite);
	m_window.display();
	level2p = std::make_unique<level2>(*this);
	loadingSprite.setTexture(loading);
	m_window.draw(loadingSprite);
	m_window.display();
	level3p = std::make_unique<level3>(*this);
	loadingSprite.setTexture(loading2);
	m_window.draw(loadingSprite);
	m_window.display();
	m_MainMenu = std::make_unique<MainMenu>(*this);
	loadingSprite.setTexture(loading3);
	m_window.draw(loadingSprite);
	m_window.display();
	m_Options = std::make_unique<OptionsScreen>(*this);
	loadingSprite.setTexture(loading);
	m_window.draw(loadingSprite);
	m_window.display();
	m_Splash = std::make_unique<SplashScreen>(*this);
	loadingSprite.setTexture(loading2);
	m_window.draw(loadingSprite);
	m_window.display();
	m_gameOver = std::make_unique<GameOver>(*this);
	loadingSprite.setTexture(loading3);
	m_window.draw(loadingSprite);
	m_window.display();
	m_Pause = std::make_unique<Pause>(*this);
	loadingSprite.setTexture(loading);
	m_window.draw(loadingSprite);
	m_window.display();
	m_Credits = std::make_unique<Credits>(*this);
	loadingSprite.setTexture(loading2);
	m_window.draw(loadingSprite);
	m_window.display();
	m_buffer = m_manager->m_songHolder["music"];
	music.setBuffer(m_buffer);
	music.setLoop(true);
	music.setVolume(100);
	music.play();
}


Game::~Game()
{
}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 30.f); // 30 fps
	while (m_window.isOpen())
	{
		processEvents(); 
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type)
		{
			m_window.close();
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	switch (m_currentGameState)
	{
	case GameStates::Splash:
		m_Splash->update();
		break;
	case GameStates::Menu:
		m_MainMenu->update();
		break;
	case GameStates::Options:
		m_Options->update();
		break;
	case GameStates::Play:
		level->update(t_deltaTime.asSeconds());
		break;
	case GameStates::levelComplete:
		m_gameOver->update();
		break;
	case GameStates::level2S:
		level2p->update(t_deltaTime.asSeconds());
		break;
	case GameStates::level3S:
		level3p->update(t_deltaTime.asSeconds());
		break;
	case GameStates::PauseScreen:
		m_Pause->update();
		break;
	case GameStates::CreditsScreen:
		m_Credits->update();
		break;
	default:
		break;
	}

	if (m_exitGame)
	{
		m_window.close();
	}

}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	view.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1920, 1080)));
	m_window.setView(view);
	m_window.clear(sf::Color::White);
	switch (m_currentGameState)
	{
	case GameStates::Splash:
		m_Splash->render(m_window);
		break;
	case GameStates::Menu:
		m_MainMenu->render(m_window);
		break;
	case GameStates::Options:
		m_Options->render(m_window);
		break;
	case GameStates::Play:
		level->draw(m_window);
		break;
	case GameStates::levelComplete:
		m_gameOver->render(m_window);
		break;
	case GameStates::level2S:
		level2p->draw(m_window);
		break;
	case GameStates::level3S:
		level3p->draw(m_window);
		break;
	case GameStates::PauseScreen:
		m_Pause->render(m_window);
		break;
	case GameStates::CreditsScreen:
		m_Credits->render(m_window);
		break;
	default:
			break;
	}

	m_window.display();
}

// function to change the games current gamestate
void Game::changeGameStates(GameStates gameState)
{
	m_currentGameState = gameState;
}