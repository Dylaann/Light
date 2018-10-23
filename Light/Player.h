#ifndef PLAYER
#define PLAYER

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "XB0XCONTROLLER.h"
#include"Box2D\Box2D.h"
#include "Key.h"
#include "door.h"
#include "Game.h"
#include "Particles.h"

class Game;
class Level1;



class Player
{
public:
	Player(b2World & world, std::string filename, float x, float y, float const SCALE, bool set);
	~Player();
	sf::Vector2f getPosition();
	
	void Update(float deltaTime, sf::View & v);
	void Draw(sf::RenderWindow& window);
	float m_battery = 0;
	float m_batterySpeed = 0.5;
	b2CircleShape m_headCollider;
	bool jump = false;
	b2Body* m_body;
	b2Body* m_body2;

private:


	sf::Sprite m_batterySprite;
	sf::Texture m_batteryTexture;
	sf::Texture m_batteryTexture1;
	sf::Texture m_batteryTexture2;
	sf::Texture m_batteryTexture3;
	sf::Texture m_batteryTexture4;
	sf::Texture m_batteryTexture5;


	sf::Clock m_clock;

	std::string Battery = "Battery";

	float m_batteryValue = 100;

	sf::Texture m_texture;
	Animation *running;
	Animation *idleA;
	XboxController m_xbox;
	unsigned int row;
	float speed;
	float velocity = 1;
	float gravity = 9.8;
	bool faceRight;
	bool keyDraw = false;
	b2BodyDef m_bodyDef;
	b2BodyDef m_bodyDef2;
	
	b2CircleShape m_shape;
	b2FixtureDef m_fixtureDef;
	b2FixtureDef m_fixtureDef2;
	sf::Sprite m_sprite;

	sf::Shader m_shader;
	sf::Sprite m_shaderSprite;
	sf::Sprite m_testSprite;
	sf::Sprite m_keyIcon;
	sf::Texture m_blank;
	sf::Texture m_testT;
	sf::Texture m_Idle;
	sf::Texture m_keyIconT;
	std::unique_ptr<Door>door;
	std::unique_ptr<Key>key;
	bool m_idle;
	bool m_runningB = false;
	sf::Vector2f direction = sf::Vector2f(0, 0);
	float wait = 1;
	float jumpoften = 0;
	sf::SoundBuffer m_buffer2;
	sf::SoundBuffer m_buffer3;
	sf::Sound m_runSound;
	sf::Sound m_jumpSound;

	Particles* m_dust;
};
#endif
