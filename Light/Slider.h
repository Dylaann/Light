#pragma once
#include<SFML\Graphics.hpp>
#include <iostream>
#include"Label.h"
#include"Widget.h"

//sliders
class Slider : public Widget {

public:
	Slider(float x, float y, float value, std::string s);

	void getFocus() override; //gain highlight
	void loseFocus() override; //lose highlight
	bool checkFocus()override; //check for focus

	void update()override; //update
	void draw(sf::RenderWindow &window)override; //draw
	int getValue(); //get sliders value
	void increaseValue(); //increase rect length
	void decreaseValue(); //decrease it

private:

	sf::RectangleShape m_innerRect; //inner rectangle

	float m_rectX = 380;
	float m_rectY = 20;
	float m_val; //slider value

	sf::Font m_font;
	sf::Text m_text;

	sf::Shader m_shader;
	sf::Sprite m_shaderSprite;
	sf::Texture m_blank;
	float totalTime = 0;

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 30.f);

};
