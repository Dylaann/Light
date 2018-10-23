#include"CheckBox.h"

//checkbox
CheckBox::CheckBox(std::string s, float x, float y) :
	Widget()
{
	m_id = "checkbox";
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

	m_shader.setUniform("pos", sf::Vector2f(x - 100, 1080 - ((y + 170))));

	m_shaderSprite.setTexture(m_blank);
	m_shaderSprite.setPosition(0, 0);
	m_shaderSprite.setScale(10, 8);

	m_icon.setFillColor(sf::Color::White);
	m_icon.setOutlineColor(sf::Color::White);
	m_icon.setPosition(x - 5, y + 150);
	m_icon.setScale(10, 8);
	m_icon.setSize(sf::Vector2f(5, 5));
	m_icon.setOutlineThickness(1.3);
	m_isActive = false;
	m_hasFocus = false;

	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition((x + 100), y + 100);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(100);

	m_rect.setPosition(x - 10, y + 200);
	m_rect.setSize(sf::Vector2f((m_icon.getGlobalBounds().width + m_text.getGlobalBounds().width) + 50, m_text.getGlobalBounds().height + 50));
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::Transparent);
	m_rect.setOutlineThickness(2);
}

//draw the components of the radiobutton
void CheckBox::draw(sf::RenderWindow &window)
{
	if (m_hasFocus == true && isActive == true)
	{
		window.draw(m_shaderSprite, &m_shader);
		window.draw(m_text);
		window.draw(m_icon);
		window.draw(m_rect);
	}
	else if (isActive)
	{
		window.draw(m_text);
		window.draw(m_icon);
		window.draw(m_rect);
	}
}

//check focus of the radiobutton
bool CheckBox::checkFocus()
{
	return m_hasFocus;
}

//make it get focus
void CheckBox::getFocus()
{
	m_hasFocus = true;
}

//make it lose focus
void CheckBox::loseFocus()
{
	m_hasFocus = false;
}

//set button to active
void CheckBox::getActive()
{
	m_isActive = true;
}
//set inactive
void CheckBox::loseActive()
{
	m_isActive = false;
}
//update the radio button
void CheckBox::update()
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

	if (m_isActive) //if active fill the circle
	{
		m_icon.setFillColor(sf::Color::Black);

	}
	else {
		m_icon.setFillColor(sf::Color::White);
	}

}
//check for active
bool CheckBox::checkActive()
{
	return m_isActive;
}