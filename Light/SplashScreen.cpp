#include "SplashScreen.h"

SplashScreen::SplashScreen(Game & game) :
	m_game(&game)
{
	m_title = new Label("Light", 50, 50);
	m_gui.addLabel(m_title);
	m_play = new Label("Press Start", 50, 600);
	m_gui.addLabel(m_play);

	m_title->changeTextSize(300);
	m_play->changeTextSize(100);

	if (!m_shader.loadFromFile("ASSETS/SHADERS///SplashScreen.frag", sf::Shader::Fragment))
	{
		std::cout << "frag shader failed to load" << std::endl;         //load shader
	}

	if (!m_blank.loadFromFile("ASSETS/IMAGES///Blank.png"))
	{

	}

	m_shader.setUniform("resolution", sf::Vector2f(1920, 1080));

	m_shaderSprite.setTexture(m_blank);
	m_shaderSprite.setPosition(0, 0);
	m_shaderSprite.setScale(10, 8);
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::render(sf::RenderWindow & window)
{
	window.draw(m_shaderSprite, &m_shader);
	m_gui.draw(window);
}

void SplashScreen::update()
{
	m_xbox.update();
	timeSinceLastUpdate += clock.restart();
	m_shader.setUniform("time", timeSinceLastUpdate.asSeconds());
	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) || m_xbox.m_currentState.Start == true && !m_xbox.m_previousState.Start)
	{
		goMain();
	}
}


void SplashScreen::goMain()
{
	m_game->changeGameStates(GameStates::Menu);
}