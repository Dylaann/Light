#include "Pause.h"

Pause::Pause(Game & game) :
	m_game(&game)
{
	m_title = new Label("Game \n Paused", 50, 50);
	m_gui.addLabel(m_title);
	m_play = new Label("X: Continue", 50, 700);
	m_gui.addLabel(m_play);
	m_quit = new Label("Back: Quit", 50, 800);
	m_gui.addLabel(m_quit);

	m_title->changeTextSize(120);
	m_play->changeTextSize(80);
	m_quit->changeTextSize(80);

	if (!m_shader.loadFromFile("ASSETS/SHADERS///SplashScreen.frag", sf::Shader::Fragment))
	{
		std::cout << "frag shader failed to load" << std::endl;         //load shader
	}

	if (!m_blank.loadFromFile("ASSETS/IMAGES///Blank.png"))
	{

	}

	m_boxSound.setBuffer(m_buffer);

	m_shader.setUniform("resolution", sf::Vector2f(1920, 1080));

	m_shaderSprite.setTexture(m_blank);
	m_shaderSprite.setPosition(0, 0);
	m_shaderSprite.setScale(10, 8);
}

Pause::~Pause()
{

}

void Pause::render(sf::RenderWindow & window)
{
	window.draw(m_shaderSprite, &m_shader);
	m_gui.draw(window);
}

void Pause::update()
{
	if (!music)
	{
		m_boxSound.play();
		music = true;
	}
	
	m_xbox.update();
	timeSinceLastUpdate += clock.restart();
	m_shader.setUniform("time", timeSinceLastUpdate.asSeconds());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || m_xbox.m_currentState.X == true && !m_xbox.m_previousState.X)
	{
		exit();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || m_xbox.m_currentState.Back == true && !m_xbox.m_previousState.Back)
	{
		m_game->changeGameStates(GameStates::Menu);
	}
}

void Pause::exit()
{
	music = false;
	m_boxSound.stop();

	if (m_game->m_gameOver->level1Complete && m_game->m_gameOver->level2Complete)
	{
		m_game->changeGameStates(GameStates::level3S);
	}
	else if (m_game->m_gameOver->level1Complete && !m_game->m_gameOver->level2Complete)
	{
		m_game->changeGameStates(GameStates::level2S);
	}
	else
	{
		m_game->changeGameStates(GameStates::Play);
	}
}
