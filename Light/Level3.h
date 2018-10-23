#ifndef LEVEL3
#define LEVEL3


#include <SFML/Graphics.hpp>
#include <tmxlite\Map.hpp>
#include "tmxlite\SFMLOrthogonalLayer.hpp"
#include "Box2D\Box2D.h"
#include "Block.h"
#include "Player.h"
#include "Crate.h"
#include "Sphere.h"
#include "door.h"
#include "Key.h"
#include "Game.h"
#include "Battery.h"
#include "XB0XCONTROLLER.h"
#include "Game.h"


class Player;
class Game;

class level3 {

public:
	level3(Game &game);
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	void goMenu();
	bool win = false;

private:
	GUI m_gui; //gui
	void loadMap();
	void loadDynamicMap();
	sf::Texture texture;
	std::vector<MapLayer * >map1;
	tmx::Map map;
	sf::RenderWindow window;
	std::unique_ptr<Player>player;
	sf::Texture playerTexture;
	sf::Vector2u textureSize;
	std::vector<Block *>blocks;
	std::unique_ptr<Crate>crate;
	std::unique_ptr<Sphere>sphere;
	std::unique_ptr<Door>door;
	std::unique_ptr<Key>key;
	std::unique_ptr<Battery>battery;
	XboxController m_xbox;
	Label* m_displayText;
	Label* m_crateText;
	Label* m_collectedText;
	Label* m_goalText;
	b2Vec2 m_gravity;
	b2World m_world;
	Game *m_game;
	sf::Texture levelThreeT;
	sf::Sprite bg3;

	sf::View view1;
	sf::View view2;

	sf::Sprite m_keyIcon;
	sf::Texture m_keyIconT;

	sf::Sprite m_ballIcon;
	sf::Texture m_ballIconT;
	bool ballCollected = false;

	void reset();


};
#endif