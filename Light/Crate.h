#ifndef CRATE_H
#define CRATE_H

#include"Box2D\Box2D.h"
#include<SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include "ResourceManager.h"

class Crate {

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	b2World *m_world;
	

public:
	Crate(b2World& world, std::string filename, float x, float y, float const SCALE);
	void Draw(sf::RenderWindow &window);
	sf::Vector2f getPos();
	void Update();
	void destroyBody();
	sf::SoundBuffer m_buffer4;
	sf::Sound m_crateSound;
	bool m_moving = false;
};

#endif // !CRATE_H