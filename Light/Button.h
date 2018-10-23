#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Label.h"
#include "Widget.h"
#include <functional>

class Button : public Widget       //button ui element
{
public:
	Button(std::string s, float x, float y); //constructor
	Button(std::string s, float x, float y, int size);
	Button(std::string s, float x, float y, sf::Color color, std::string tag); //overloaded
	~Button();
	void getFocus() override; //make button the current highlighted element
	void loseFocus()override; //lose highlight
	bool checkFocus()override;   //check if highlighed
	void update()override; //update loop
	void draw(sf::RenderWindow &window)override; //draw loop
	void setRectColor(sf::Color color); //set the rect color of button
	void endAnim(); //animation transition
	void changeTextSize(int size);

protected:
	sf::RectangleShape m_rect; //rectangle that will surround text
	bool m_hasFocus; //simple bool for check
	sf::Font m_font; //font
	sf::Text m_text; //text object
	float posX; //xpos
	float posY;//ypos

	sf::Shader m_shader;
	sf::Sprite m_shaderSprite;
	sf::Texture m_blank;
	float totalTime = 0;

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 30.f);


};
