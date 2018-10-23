#ifndef DOOR_H
#define DOOR_H

#include"Box2D\Box2D.h"
#include<SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include "ResourceManager.h"

class Door {

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	sf::SoundBuffer m_buffer;

public:
	Door(b2World& world, std::string filename, float x, float y, float const SCALE);
	void Draw(sf::RenderWindow &window);
	sf::Vector2f getPos();
	void Update();
	sf::Sound m_doorSound;
};

#endif // !DOOR_H