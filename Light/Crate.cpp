#include "Crate.h"

Crate::Crate(b2World & world, std::string filename, float x, float y, float const SCALE) : m_world{ &world }
{
	if (!m_texture.loadFromFile("crate.png"))
	{
		std::cout << "Error Loading Block Texture!" << std::endl;
	}
	if (!m_buffer4.loadFromFile("ASSETS\\SOUNDS\\crate2.wav"))
	{
	}
	m_crateSound.setBuffer(m_buffer4);
	m_crateSound.setVolume(60);


	m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	m_bodyDef.type = b2_dynamicBody;
	m_body = world.CreateBody(&m_bodyDef);
	m_shape.SetAsBox((64.f / 2) / SCALE, (64.f / 2) / SCALE);
	m_fixtureDef.density = 10.0f;
	m_fixtureDef.friction = 1.0f;
	m_fixtureDef.restitution = 0.0f;
	
	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	//m_body->SetFixedRotation(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(64 / 2, 64 / 2);
	m_sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
	
}
void Crate::Update()
{

	if (m_body->GetLinearVelocity().x >= 1)
	{
		if (m_crateSound.getStatus() != m_crateSound.Playing)
		{
			m_crateSound.play();
			std::cout << "playing" << std::endl;
		}
		
	}
	
	if (m_body->GetLinearVelocity().x <= -1)
	{
		if (m_crateSound.getStatus() != m_crateSound.Playing)
		{
			m_crateSound.play();
			std::cout << "playing" << std::endl;
		}

	}


	m_moving = true;
	
	m_sprite.setRotation(180 / b2_pi * m_body->GetAngle());
	m_sprite.setPosition(m_body->GetPosition().x * 30, m_body->GetPosition().y * 30);
}
void Crate::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}


sf::Vector2f Crate::getPos()
{
	return m_sprite.getPosition();
	
}

void Crate::destroyBody()
{
	m_world->DestroyBody(m_body);
}



