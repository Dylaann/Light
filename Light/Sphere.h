#ifndef SPHERE_H
#define SPHERE_H

#include"Box2D\Box2D.h"
#include<SFML\Graphics.hpp>
#include <string>
#include <iostream>

class Sphere {

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	b2BodyDef m_bodyDef;
	b2CircleShape m_shape;
	b2FixtureDef m_fixtureDef;
	b2World *m_world;

public:
	Sphere(b2World& world, std::string filename, float x, float y, float const SCALE);
	void Draw(sf::RenderWindow &window);
	sf::Vector2f getPos();
	void Update();
	void destroyBody();
	b2Body* m_body;

};

#endif // !SPHERE_H