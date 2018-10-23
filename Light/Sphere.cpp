#include "Sphere.h"

Sphere::Sphere(b2World & world, std::string filename, float x, float y, float const SCALE) : m_world{ &world }
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/football2.png"))
	{
		std::cout << "Error Loading Block Texture!" << std::endl;
	}
	m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	m_bodyDef.type = b2_dynamicBody;
	m_body = world.CreateBody(&m_bodyDef);
	//m_shape.SetAsCircle((64.f / 2) / SCALE, (64.f / 2) / SCALE);
	m_shape.m_radius = 0.75f;
	m_fixtureDef.density = 0.3f;
	m_fixtureDef.friction = 0.5f;
	m_fixtureDef.restitution = 0.3f;
	m_fixtureDef.shape = &m_shape;
	m_body->CreateFixture(&m_fixtureDef);
	m_body->SetFixedRotation(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(50 / 2, 50 / 2);
	//m_fixtureDef
	m_sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);

}
void Sphere::Update()
{
	m_sprite.setRotation(180 / b2_pi * m_body->GetAngle());
	m_sprite.setPosition(m_body->GetPosition().x * 30, m_body->GetPosition().y * 30);
}
void Sphere::destroyBody()
{
	m_world->DestroyBody(m_body);
}

void Sphere::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}


sf::Vector2f Sphere::getPos()
{
	return m_sprite.getPosition();
}

