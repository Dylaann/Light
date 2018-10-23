#ifndef KEY
#define KEY

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include"Box2D\Box2D.h"
#include "Animation.h"

class Key {

public:
	Key(b2World & world, float x, float y, float SCALE);
	~Key();
	void update(float deltaTime);
	void render(sf::RenderWindow &window);
	void destroyBody();
	bool collected = false;
	sf::Vector2f getPosition();
	sf::SoundBuffer m_buffer;
	sf::Sound m_keySound;

	b2Body* m_body;
	b2BodyDef m_bodyDef;

	

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::unique_ptr<ResourceManager> m_manager; //resource manager
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	unsigned int row = 0;
	std::unique_ptr<Animation>animation;
	b2World *m_world;

};
#endif
