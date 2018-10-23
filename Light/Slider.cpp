#include"Slider.h"
//slider ui element
Slider::Slider(float x, float y, float value, std::string s) :
	Widget()
{
	if (!m_font.loadFromFile("ASSETS\\FONTS\\PAPYRUS.ttf"))
	{
		//error message
	}

	if (!m_shader.loadFromFile("ASSETS/SHADERS///Gui.frag", sf::Shader::Fragment))
	{
		std::cout << "frag shader failed to load" << std::endl;         //load shader
	}

	if (!m_blank.loadFromFile("ASSETS/IMAGES///Blank.png"))
	{

	}

	m_shader.setUniform("pos", sf::Vector2f(x - 100, 2160 - ((y + 70) * 2)));

	m_shaderSprite.setTexture(m_blank);
	m_shaderSprite.setPosition(0, 0);
	m_shaderSprite.setScale(10, 8);


	m_text.setFont(m_font);
	m_text.setString(s);
	m_text.setPosition(x - 30, y - 5);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(100);

	m_val = value;
	m_id = "slider";
	m_hasFocus = false;
	//outer rectangle
	m_rect.setPosition(x + (m_text.getGlobalBounds().width), y + 50);
	m_rect.setSize(sf::Vector2f(400.0f, 40.0f));
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::Transparent);
	m_rect.setOutlineThickness(1);

	//inner rectangle, size dictacted by a value
	m_innerRect.setPosition(x + (m_text.getGlobalBounds().width) + 10, y + 60);
	m_innerRect.setSize(sf::Vector2f(m_rectX, m_rectY));
	m_innerRect.setFillColor(sf::Color::White);
	m_innerRect.setOutlineColor(sf::Color::Black);
	m_innerRect.setOutlineThickness(1);


}

//make slider get focus
void Slider::getFocus()
{
	m_hasFocus = true;
}
//make it lose focus
void Slider::loseFocus()
{
	m_hasFocus = false;
}

//check its current focus
bool Slider::checkFocus()
{
	return m_hasFocus;
}

//decrease the size of the rectangle
void Slider::decreaseValue()
{
	if (m_val > 0)
	{
		m_val--;
	}
}
//increase the size of the rectangle
void Slider::increaseValue()
{
	if (m_val < 100)
	{
		m_val++;
	}
}

//draw the components of the slider
void Slider::draw(sf::RenderWindow &window)
{
	if (m_hasFocus == true && isActive == true)
	{
		window.draw(m_shaderSprite, &m_shader);
		window.draw(m_text);
		window.draw(m_innerRect);
		window.draw(m_rect);
	}
	else if (isActive)
	{
		window.draw(m_text);
		window.draw(m_innerRect);
		window.draw(m_rect);
	}

}
//return value that represents the slider
int Slider::getValue()
{
	return m_val;
}

//update the slider component
void Slider::update()
{

	m_innerRect.setSize(sf::Vector2f(m_rectX*(m_val / 100), m_rectY)); //chaneg the rectangles size based on the value
	timeSinceLastUpdate += clock.restart();

	if (m_hasFocus == true && isActive == true)
	{
		m_rect.setOutlineColor(sf::Color::White);
		m_text.setFillColor(sf::Color::White);
		m_innerRect.setFillColor(sf::Color::White);
		m_shader.setUniform("time", timeSinceLastUpdate.asSeconds());
	}
	else
	{
		m_text.setFillColor(sf::Color(255, 255, 255, 50));
		m_innerRect.setFillColor(sf::Color(255, 255, 255, 50));
		m_rect.setOutlineColor(sf::Color(255, 255, 255, 50));
	}

}