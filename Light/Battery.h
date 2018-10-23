#ifndef BATTERY
#define BATTERY

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include"Box2D\Box2D.h"

class Battery {

public:
	Battery(b2World & world, float x, float y, float SCALE);
	~Battery();
	void update();
	void render(sf::RenderWindow &window);
	void destroyBody();
	bool collected = false;
	sf::Vector2f getPosition();
	sf::SoundBuffer m_buffer;
	sf::Sound m_keySound;

	b2Body* m_body;
	b2BodyDef m_bodyDef;
	sf::Sprite m_sprite;


private:
	sf::Texture m_texture;
	std::unique_ptr<ResourceManager> m_manager; //resource manager
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	b2World *m_world;

};
#endif

