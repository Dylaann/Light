#include "door.h"

Door::Door(b2World & world, std::string filename, float x, float y, float const SCALE)
{
	if (!m_texture.loadFromFile("doorT.png"))
	{
		std::cout << "Error Loading Block Texture!" << std::endl;
	}

	if (!m_buffer.loadFromFile("ASSETS\\SOUNDS\\Door.wav"))
	{
	}
	m_doorSound.setBuffer(m_buffer);

//	m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
//	m_bodyDef.type = b2_staticBody;
//	m_body = world.CreateBody(&m_bodyDef);
//	m_shape.SetAsBox((64.f / 2) / SCALE, (64.f / 2) / SCALE);
	//m_fixtureDef.density = 0.0f;
	///m_fixtureDef.friction = 0.0f;
//	m_fixtureDef.restitution = 0.0f;
	//m_fixtureDef.shape = &m_shape;
//	m_body->CreateFixture(&m_fixtureDef);
	//m_body->SetFixedRotation(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(64 / 2, 64 / 2);
	m_sprite.setPosition(500 ,730);
	

}
void Door::Update()
{
//	m_sprite.setRotation(180 / b2_pi * m_body->GetAngle());
//	m_sprite.setPosition(m_body->GetPosition().x * 30, m_body->GetPosition().y * 30);
}
void Door::Draw(sf::RenderWindow& window)
{


	window.draw(m_sprite);

}


sf::Vector2f Door::getPos()
{
	return m_sprite.getPosition();
}