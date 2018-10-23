#ifndef CREDITS
#define CREDITS

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include <vector>
#include "Game.h"
#include <string>

class Game;

class Credits
{
public:
	Credits(Game &game);
	~Credits();
	void update();
	void render(sf::RenderWindow &window);

private:

	Game *m_game; //game object

	void setUpText(sf::Text *text, sf::Font &font, unsigned int &size, sf::Color &col, std::string &words, sf::Vector2f &pos);
	void goMain();
	void reset();

	/// <summary>
	/// Resource manager
	/// </summary>
	std::unique_ptr<ResourceManager> m_rm;

	/// <summary>
	/// Setup
	/// </summary>
	unsigned int End = 200;
	unsigned int head = 100;
	unsigned int title = 60;
	unsigned int body = 40;

	sf::Font m_titleFont;
	sf::Font m_bodyFont;

	sf::Color white = sf::Color::White;

	/// <summary>
	/// Text
	/// </summary>
	sf::Text * m_title;
	sf::Text * Dylan;
	sf::Text * DylansStuff;
	sf::Text * Dave;
	sf::Text * DavesStuff;
	sf::Text * Light;
	sf::Text * dylanEmail;
	sf::Text * daveEmail;

	std::vector<sf::Text *> m_texts;

	/// <summary>
	/// Shader
	/// </summary>
	sf::Shader m_shader;
	sf::Sprite m_shaderSprite;
	sf::Texture m_blank;
	float totalTime = 0;

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 30.f);

	sf::Clock clock2;
	sf::Time time2 = sf::Time::Zero;
	bool timeStarted = false;

	XboxController m_xbox; //xbox controller
};
#endif // !
