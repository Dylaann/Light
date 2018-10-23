#include "Battery.h"

Battery::Battery(b2World & world, float x, float y, float SCALE) : m_world{ &world }
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\battery.png"))
	{
	}

	//if (!m_buffer.loadFromFile("ASSETS\\SOUNDS\\keys.wav"))
	//{
	//}
	//m_keySound.setBuffer(m_buffer);

	m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	m_bodyDef.type = b2_staticBody;
	m_body = world.CreateBody(&m_bodyDef);

	m_shape.SetAsBox((50.f / 3) / SCALE, (50.f / 3) / SCALE);
	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(true);

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(175 / 2, 175 / 2);
	m_sprite.setPosition(m_body->GetPosition().x  * SCALE, m_body->GetPosition().y  * SCALE);
	m_sprite.scale(sf::Vector2f(0.3, 0.3));
	m_sprite.rotate(-90);
}

Battery::~Battery()
{
}

void Battery::update()
{
	if (collected == false)
	{
		m_sprite.setPosition(m_body->GetPosition().x * 30, m_body->GetPosition().y * 30);
		m_sprite.setTexture(m_texture);
	}
}

void Battery::render(sf::RenderWindow & window)
{
	if (collected == false)
	{
		window.draw(m_sprite);
	}
}


void Battery::destroyBody()
{
	m_world->DestroyBody(m_body);
}


sf::Vector2f Battery::getPosition()
{
	return sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y);
}