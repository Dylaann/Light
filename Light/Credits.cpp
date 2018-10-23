#include "Credits.h"

Credits::Credits(Game & game) :
	m_game(&game)
{
	m_rm = std::make_unique<ResourceManager>();

	if (!m_shader.loadFromFile("ASSETS\\SHADERS\\Gui.frag", sf::Shader::Fragment))
	{

	}

	if (!m_blank.loadFromFile("ASSETS/IMAGES///Blank.png"))
	{

	}

	m_shader.setUniform("pos", sf::Vector2f(400, 1080 - 350));

	m_shaderSprite.setTexture(m_blank);
	m_shaderSprite.setPosition(0, 0);
	m_shaderSprite.setScale(10, 20);

	m_titleFont = m_rm->m_fontHolder["pap"];
	m_bodyFont = m_rm->m_fontHolder["ari"];
	m_title = new sf::Text();
	Dylan = new sf::Text();
	DylansStuff = new sf::Text();
	Dave = new sf::Text();
	DavesStuff = new sf::Text();
	Light = new sf::Text();
	dylanEmail = new sf::Text();
	daveEmail = new sf::Text();

	reset();

	m_texts.push_back(Dylan);
	m_texts.push_back(DylansStuff);
	m_texts.push_back(Dave);
	m_texts.push_back(DavesStuff);
	m_texts.push_back(Light);
}

Credits::~Credits()
{

}

void Credits::update()
{

	m_xbox.update();
	timeSinceLastUpdate += clock.restart();
	m_shader.setUniform("time", timeSinceLastUpdate.asSeconds());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || m_xbox.m_currentState.Back == true && !m_xbox.m_previousState.Back)
	{
		reset();
		goMain();
	}

	for (auto text : m_texts)
	{
		text->setPosition(text->getPosition().x, text->getPosition().y - 2);

		if (text->getPosition().y > 250 && text->getPosition().y < 500)
		{
			float dist = sqrt(((text->getPosition().x - text->getPosition().x) * (text->getPosition().x - text->getPosition().x)) + ((text->getPosition().y - 250)* (text->getPosition().y - 250)));

			text->setFillColor(sf::Color(255, 255, 255, (int)(255 * (dist / 250))));
		}

		if (text->getString() == "Light")
		{
			if (text->getPosition().y == 400)
			{
				text->setPosition(sf::Vector2f(700, 402));
				if (!timeStarted)
				{
					clock2.restart();
					timeStarted = true;
				}

				if (timeStarted)
				{
					if (clock2.getElapsedTime().asSeconds() > 0)
					{
						text->setFillColor(sf::Color(255, 255, 255, (int)(255 * ((5 / clock2.getElapsedTime().asSeconds()) / 5))));
					}
				}

				if (clock2.getElapsedTime().asSeconds() > 5)
				{
					text->setPosition(sf::Vector2f(700, -10));
				}
			}

			if (text->getPosition().y < 0)
			{
				reset();
				goMain();
			}


		}
	}



}

void Credits::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);

	window.draw(m_shaderSprite, &m_shader);

	window.draw(*m_title);

	for (auto text : m_texts)
	{
		window.draw(*text);
	}

	window.draw(*dylanEmail);
	window.draw(*daveEmail);
}

void Credits::setUpText(sf::Text *text, sf::Font &font, unsigned int &size, sf::Color &col, std::string &words, sf::Vector2f &pos)
{
	text->setFont(font);
	text->setCharacterSize(size);
	text->setFillColor(col);
	text->setString(words);
	text->setPosition(pos);
}

void Credits::goMain()
{
	m_game->changeGameStates(GameStates::Menu);
}

void Credits::reset()
{
	timeStarted = false;
	setUpText(m_title, m_titleFont, head, white, std::string("CREDITS"), sf::Vector2f(650, 100));
	setUpText(Dylan, m_titleFont, title, white, std::string("DYLAN:"), sf::Vector2f(600, 1080));
	setUpText(DylansStuff, m_titleFont, title, white, std::string("Gui \n VFX \n Physics"), sf::Vector2f(620, 1180));
	setUpText(Dave, m_titleFont, title, white, std::string("DAVID:"), sf::Vector2f(600, 1680));
	setUpText(DavesStuff, m_titleFont, title, white, std::string("Animation \n Level Design \n Physics"), sf::Vector2f(620, 1780));
	setUpText(Light, m_titleFont, End, white, std::string("Light"), sf::Vector2f(700, 2280));

	setUpText(daveEmail, m_titleFont, body, white, std::string("davidogorman@gmx.com"), sf::Vector2f(20, 900));
	setUpText(dylanEmail, m_titleFont, body, white, std::string("Dyl.mrph@gmail.com"), sf::Vector2f(20, 1000));
}