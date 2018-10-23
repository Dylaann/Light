#include"Button.h"

//constructor
Button::Button(std::string s = "", float x = 0, float y = 0) :
	Widget()
{
	isActive = true; //starts active

	m_id = "button";

	if (!m_font.loadFromFile("ASSETS\\FONTS\\PAPYRUS.ttf"))
	{
	}

	if (!m_shader.loadFromFile("ASSETS/SHADERS///Gui.frag", sf::Shader::Fragment))
	{
		std::cout << "frag shader failed to load" << std::endl;         //load shader
	}

	if (!m_blank.loadFromFile("ASSETS/IMAGES///Blank.png"))
	{

	}

	m_hasFocus = false; //no focus
	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition(x, y);
	m_text.setFillColor(sf::Color::White); //no focus means element is white
	m_text.setCharacterSize(100);

	m_rect.setPosition(x - 5, y);
	m_rect.setSize(sf::Vector2f(m_text.getGlobalBounds().width + 50, m_text.getGlobalBounds().height + 50)); //dynamic rectangle sizing based on text
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::Transparent); //set to transparent
	m_rect.setOutlineThickness(2);
	animEnd = false;
	posX = 0;

	m_shader.setUniform("pos", sf::Vector2f(m_rect.getPosition().x - 80, 1080 - ((m_rect.getPosition().y + 60))));

	m_shaderSprite.setTexture(m_blank);
	m_shaderSprite.setPosition(0, 0);
	m_shaderSprite.setScale(20, 16);
}

Button::Button(std::string s, float x, float y, int size)
{
	isActive = true; //starts active

	m_id = "button";

	if (!m_font.loadFromFile("ASSETS\\FONTS\\PAPYRUS.ttf"))
	{
	}

	m_hasFocus = false; //no focus
	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition(x, y);
	m_text.setFillColor(sf::Color::White); //no focus means element is white
	m_text.setCharacterSize(size);

	m_rect.setPosition(x - 5, y);
	m_rect.setSize(sf::Vector2f(m_text.getGlobalBounds().width + 10, m_text.getGlobalBounds().height + 15)); //dynamic rectangle sizing based on text
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::Transparent); //set to transparent
	m_rect.setOutlineThickness(2);
	animEnd = false;
	posX = 0;
}


//alternative constructor that incorporates tags
Button::Button(std::string s, float x, float y, sf::Color color, std::string tag)
{
	isActive = true;
	m_tag = tag;
	m_id = "button";
	if (!m_font.loadFromFile("ASSETS\\FONTS\\PAPYRUS.ttf"))
	{
		//error message
	}
	m_hasFocus = false;
	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition(x, y);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(32);

	m_rect.setPosition(x - 5, y);
	m_rect.setSize(sf::Vector2f(m_text.getGlobalBounds().width + 10, m_text.getGlobalBounds().height + 15));
	m_rect.setFillColor(color);
	m_rect.setOutlineColor(sf::Color::Transparent);
	m_rect.setOutlineThickness(2);
	animEnd = false;
}

//deconstruction
Button::~Button()
{
}

//get focus on this element
void Button::getFocus()
{

	m_hasFocus = true;
}
//lose focus on this element
void Button::loseFocus()
{
	m_hasFocus = false;
}
//check elements focus
bool Button::checkFocus()
{
	return m_hasFocus;
}

//update loop
void Button::update()
{
	timeSinceLastUpdate += clock.restart();

	if (m_hasFocus == true && isActive == true)
	{
		m_text.setFillColor(sf::Color::White);
		m_rect.setOutlineColor(sf::Color::Transparent);     //turn magenta if the button has focus
		m_shader.setUniform("time", timeSinceLastUpdate.asSeconds());
	}
	else
	{
		m_text.setFillColor(sf::Color(255, 255, 255, 50));
		m_rect.setOutlineColor(sf::Color::Transparent); //back to normal if it doesnt
	}

}
//draw button
void Button::draw(sf::RenderWindow &window)
{
	if (m_hasFocus == true && isActive == true)
	{
		window.draw(m_shaderSprite, &m_shader);
		window.draw(m_text);
		window.draw(m_rect);
	}
	else if (isActive)
	{
		window.draw(m_text);
		window.draw(m_rect);
	}

}
//change color of rectangle
void Button::setRectColor(sf::Color color)
{
	m_rect.setFillColor(color);
}

//button animation
//button will do a 360 spin before callback is executed
void Button::endAnim()
{
	m_text.setFillColor(sf::Color(0, 191, 255, 255));
	animEnd = true;
}

void Button::changeTextSize(int size)
{
	m_text.setCharacterSize(size);
}
