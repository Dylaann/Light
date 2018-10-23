#include "Block.h"

Block::Block(b2World & world, std::string filename, float x, float y, float const SCALE)
{
	if (!m_texture.loadFromFile("box.png"))
	{
		std::cout << "Error Loading Block Texture!" << std::endl;
	}
	m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	m_bodyDef.type = b2_staticBody;
	m_body = world.CreateBody(&m_bodyDef);
	m_shape.SetAsBox((64.f / 2) / SCALE, (64.f / 2) / SCALE);
	m_fixtureDef.density = 1.f;
	m_fixtureDef.friction = 0.1f;
	m_fixtureDef.restitution = 0.0f;
	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(64 / 2, 64 / 2);
	m_sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
	m_sprite.setRotation(180 / b2_pi * m_body->GetAngle());
}
void Block::Update()
{
	m_sprite.setPosition(m_body->GetPosition().x * 30, m_body->GetPosition().y * 30);
}
void Block::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}


sf::Vector2f Block::getPos()
{
	return m_sprite.getPosition();
}