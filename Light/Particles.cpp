#include "Particles.h"

Particles::Particles(sf::Vector2f m_pos)
{
	if (!dustTex.loadFromFile("ASSETS/IMAGES///dust.png"))
	{

	}
	if (!dustTex2.loadFromFile("ASSETS/IMAGES///dust.png"))
	{

	}

	for (int i = 0; i < m_amount; i++)
	{
		sf::Sprite *cs = new sf::Sprite();
		cs->setTexture(dustTex);
		cs->setOrigin(dustTex.getSize().x / 5, dustTex.getSize().y / 5);
		cs->setPosition(m_pos);
		cs->setScale(0.02, 0.02);

		m_effects.push_back(cs);
	}

	/*for (int i = 0; i < m_amount; i++)
	{
		sf::CircleShape *cs = new sf::CircleShape();
		cs->setPosition(m_pos);
		cs->setRadius(2);
		cs->setFillColor(sf::Color::Color(100, 100, 100));

		m_parts.push_back(cs);
	}*/
}

Particles::~Particles()
{

}

void Particles::update(sf::Vector2f m_pos, bool left)
{


	/*for (auto part : m_parts)
	{
		if (!active)
		{
			part->setPosition(sf::Vector2f(m_pos.x, m_pos.y + 50));
		}

		if (active)
		{
			sf::Vector2f position = sf::Vector2f(rand() % 30 + (m_pos.x - 15), rand() % 10 + (m_pos.y + 50));
			part->setPosition(sf::Vector2f(position.x, position.y + speed));
		}


	}*/

	for (auto eff : m_effects)
	{
		if (!active)
		{
			eff->setPosition(sf::Vector2f(m_pos.x, m_pos.y + 50));
		}

		if (active)
		{
			sf::Vector2f position = sf::Vector2f(rand() % 30 + (m_pos.x - 15), rand() % 10 + (m_pos.y + 50));
			eff->setPosition(sf::Vector2f(position.x, position.y + (speed/100)));

			if (left)
			{
				eff->setTexture(dustTex2);
			}
			else
			{
				eff->setTexture(dustTex);
			}
		}


	}
}

void Particles::render(sf::RenderWindow & window)
{
	/*for (auto part : m_parts)
	{
		if (active)
		{
			window.draw(*part);
		}
	}*/

	for (auto eff : m_effects)
	{
		if (active)
		{
			window.draw(*eff);
		}
	}
}
