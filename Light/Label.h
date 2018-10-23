#pragma once
#include<SFML\Graphics.hpp>
#include"Widget.h"

class Label : public Widget {
public:
	Label(std::string s, float x, float y);
	Label(std::string s, float x, float y, std::string textureName); //constructors
	Label(std::string s, float x, float y, std::string textureName, std::string textureName2);
	void draw(sf::RenderWindow &window); //draw loop
	void update(); //update loop
	void setUnderLined(); //make  label underlined
	void updateText(std::string s); //change the text of the label
	void changeTextSize(int size); //change size of the label
	sf::Text m_text;

protected:
	sf::Vector2f m_pos;
	sf::Font m_font;


	//icon stuff that probably wont be used for most labels
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool hasTexture;
	bool has2Textures;
	int textSize;

	sf::Texture m_texture2;
	sf::Sprite m_sprite2;
};
