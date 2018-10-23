#ifndef PARTICLES
#define PARTICLES

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

class Particles
{
public:
	Particles(sf::Vector2f m_pos);
	~Particles();
	void update(sf::Vector2f m_pos, bool left);
	void render(sf::RenderWindow &window);
	bool active = false;

private:

	sf::Vector2f m_position;
	sf::Texture dustTex;
	sf::Texture dustTex2;

	std::vector<sf::Sprite *> m_effects;

	std::vector<sf::CircleShape *> m_parts;

	int m_life = 2;
	int speed = 0.002;
	int m_amount = 8;

	int m_left = false;

	sf::Clock timer;
};
#endif // !