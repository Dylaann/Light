#include "Key.h"

Key::Key(b2World & world, float x, float y, float SCALE) : m_world{&world}
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\key.png"))
	{
	}

	if (!m_buffer.loadFromFile("ASSETS\\SOUNDS\\keys.wav"))
	{
	}
	m_keySound.setBuffer(m_buffer);

	animation = std::make_unique<Animation>(&m_texture, sf::Vector2u(6, 1), 0.1);
	
	m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	m_bodyDef.type = b2_staticBody;
	m_body = world.CreateBody(&m_bodyDef);

	m_shape.SetAsBox((35.f / 8) / SCALE, (86.f / 8) / SCALE);
	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(35 / 2, 86 / 2);
	m_sprite.setPosition(m_body->GetPosition().x  * SCALE, m_body->GetPosition().y  * SCALE);

}

Key::~Key()
{
}

void Key::update(float deltaTime)
{

	if (collected == false)
	{
		m_sprite.setPosition(m_body->GetPosition().x * 30, m_body->GetPosition().y * 30);
		m_sprite.setTexture(m_texture);
		animation->update(row, deltaTime, true);
		m_sprite.setTextureRect(animation->uvRect);
	}
}

void Key::render(sf::RenderWindow & window)
{
	if (collected == false)
	{
		window.draw(m_sprite);
	}
}


void Key::destroyBody()
{
	m_world->DestroyBody(m_body);
}


sf::Vector2f Key::getPosition()
{
	return sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y);
}