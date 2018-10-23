#include "Level3.h"


level3::level3(Game &game) : m_gravity{ 0, 100 },
m_world{ m_gravity }, m_game(&game)
{

//	loadMap();
	loadDynamicMap();
	view1.setSize(sf::Vector2f(1920, 1080));
	view1.zoom(0.6f);

	playerTexture.loadFromFile("spriteSheet4.png");
	levelThreeT.loadFromFile("ASSETS/IMAGES/level3.png");

	bg3.setTexture(levelThreeT);
	bg3.setOrigin(190, -100);

	player = std::make_unique<Player>(m_world, "", 780, 1300, 30, false);
	textureSize = playerTexture.getSize();
	textureSize.x /= 22;
	textureSize.y /= 1;
	crate = std::make_unique<Crate>(m_world, "", 3200, 200, 30);
	sphere = std::make_unique<Sphere>(m_world, "", 1030, 1250, 30);
	door = std::make_unique<Door>(m_world, "", 500, 730, 30);
	key = std::make_unique<Key>(m_world, 2710, 1720, 30);
	battery = std::make_unique<Battery>(m_world, 2510, 1280, 30);

	m_ballIconT.loadFromFile("ASSETS\\IMAGES\\football2.png");
	m_ballIcon.setTexture(m_ballIconT);
	m_ballIcon.setPosition(player->getPosition().x, player->getPosition().y);
	m_ballIcon.setScale(1, 1);

	m_keyIconT.loadFromFile("ASSETS\\IMAGES\\keyPickup.png");
	m_keyIcon.setTexture(m_keyIconT);
	m_keyIcon.setScale(0.5, 0.5);
	
	m_displayText = new Label("Hmm, A door, I wonder \n if I can find a Key", 400, 580);
	m_gui.addLabel(m_displayText);
	m_displayText->changeTextSize(30);

	m_crateText = new Label("Huh, A crate", 1000, 660);
	m_gui.addLabel(m_displayText);
	m_crateText->changeTextSize(30);

	m_collectedText = new Label("This should work \n press X", 560, 680);
	m_gui.addLabel(m_collectedText);
	m_collectedText->changeTextSize(25);

	m_goalText = new Label("Level Complete", 400, 680);
	m_gui.addLabel(m_collectedText);
	m_goalText->changeTextSize(90);

	sphere->m_body->SetLinearVelocity(b2Vec2(10,0));
}

void level3::update(float deltaTime) {
	m_world.Step(1 / 60.f, 10, 5);
	crate->Update();
	sphere->Update();
	door->Update();
	battery->update();
	player->Update(deltaTime, view1);
	m_xbox.update();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || m_xbox.m_currentState.Start == true && !m_xbox.m_previousState.Start)
	{
		m_game->changeGameStates(GameStates::PauseScreen);
	}


	if (player->getPosition().x + 4 >= key->getPosition().x && key->collected == false)
	{
		player->m_battery = 0;
		key->collected = true;
		key->m_keySound.play();
		key->destroyBody();

	}

	std::cout << player->getPosition().x << sphere->getPos().x << std::endl;

	if (player->getPosition().x > 80)
	{
		if (player->getPosition().x > sphere->getPos().x / 30 - 4 && ballCollected == false)
		{
			player->m_battery = 0;
			ballCollected = true;
			// key->m_keySound.play();
			sphere->destroyBody();
		}
	}

	float dist = std::abs((player->getPosition().x - battery->getPosition().x) * (player->getPosition().x - battery->getPosition().x) +
	(player->getPosition().y - battery->getPosition().y) * (player->getPosition().y - battery->getPosition().y));

	std::cout << "Dist: " << dist << std::endl;
	if (dist < 0.05)
	{
		player->m_battery = 0;
		battery->collected = true;
		battery->destroyBody();
	}

	std::cout << player->getPosition().x << std::endl;
	if (ballCollected == true && key->collected == true && player->getPosition().x <= 17 && player->getPosition().x >= 14)
	{

		if (m_xbox.m_currentState.X || sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			player->m_battery = 0;
			view1.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1920, 1080)));
			view1.zoom(0.6f);
			std::cout << "Pressed" << std::endl;
			door->m_doorSound.play();
			win = true;
			m_game->m_gameOver->level3Complete = true;
			reset();
			goMenu();
		}

	}

	if (key->collected == false)
	{
		key->update(deltaTime);
	}
	else
	{
		m_keyIcon.setPosition(player->getPosition().x * 30 + 500, player->getPosition().y * 30 - 260);
	}

	if (ballCollected== true)
	{
		m_ballIcon.setPosition(player->getPosition().x * 30 + 425, player->getPosition().y * 30 - 260);
	}


	/*for (auto &block : blocks)
	{
	if (player->getPosition().y == block->getPos().y)
	{
	player->jump = true;
	}
	}
	*/

	for (auto &block : blocks)
	{
		if (player->m_body2->GetPosition().x == block->getPos().x && player->m_body2->GetPosition().y == block->getPos().y)
		{
			player->m_body->SetTransform(b2Vec2(5, 5), 0);
		}
	}

}


void level3::draw(sf::RenderWindow &window) {
	window.setView(view1);
//	window.draw(*map1.at(0));
	window.draw(bg3)
		;
	for (auto &block : blocks)
	{
		float winxright = window.getView().getCenter().x + (window.getSize().x / 2);
		float winxleft = window.getView().getCenter().x - (window.getSize().x / 2);
		float winytop = window.getView().getCenter().y + (window.getSize().y / 2);
		float winybottom = window.getView().getCenter().y - (window.getSize().y / 2);

		if (block->getPos().x > winxleft && block->getPos().x < winxright &&
			block->getPos().y < winytop && block->getPos().y > winybottom)
		{
			block->Draw(window);
		}
	}

	if (key->collected == true)
	{
		m_collectedText->draw(window);
	}
	else
	{
		m_displayText->draw(window);
		m_crateText->draw(window);
	}

	key->render(window);

	door->Draw(window);
	crate->Draw(window);
	sphere->Draw(window);
	battery->render(window);
	if (key->collected == true)
	{
		std::cout << "PosX: " << m_keyIcon.getPosition().x << "PosY: " << m_keyIcon.getPosition().y << std::endl;
	}

	player->Draw(window);

	if (key->collected == true)
	{
		window.draw(m_keyIcon);
	}

	if (ballCollected == true)
	{
		//m_collectedText->draw(window);
		window.draw(m_ballIcon);
		std::cout << "PosX: " << m_ballIcon.getPosition().x << "PosY: " << m_ballIcon.getPosition().y << std::endl;

	}

	if (win == true)
	{
		m_goalText->draw(window);
	}

	

	

}

void level3::goMenu()
{
	player->m_body->SetTransform(b2Vec2(780 / 30, 1300 / 30), 0);
	player->m_battery = 0;
	win = false;
	m_game->changeGameStates(GameStates::levelComplete);

}

void level3::loadMap()
{
	if (map.load("maps/map2.tmx"))
	{
		std::cout << "Loaded map" << map.getVersion().upper << ", " << map.getVersion().lower << std::endl;
		std::cout << map.getLayers().size() << std::endl;
		std::cout << map.getTilesets().size() << std::endl;
		map1.push_back(new MapLayer(map, 0));

		const auto& mapProperties = map.getProperties();
		std::cout << "Map has " << mapProperties.size() << " properties" << std::endl;
		for (const auto& prop : mapProperties)
		{
			std::cout << "Found property: " << prop.getName() << std::endl;
			std::cout << "Type: " << int(prop.getType()) << std::endl;
		}

		std::cout << std::endl;

		const auto& layers = map.getLayers();
		std::cout << "Map has " << layers.size() << " layers" << std::endl;
		for (const auto& layer : layers)
		{
			std::cout << "Found Layer: " << layer->getName() << std::endl;
			std::cout << "Layer Type: " << int(layer->getType()) << std::endl;

			if (layer->getType() == tmx::Layer::Type::Object)
			{
				const auto& objects = dynamic_cast<tmx::ObjectGroup*>(layer.get())->getObjects();
				std::cout << "Found " << objects.size() << " objects in layer" << std::endl;
				for (const auto& object : objects)
				{
					std::cout << "Object " << object.getName() << std::endl;
					const auto& properties = object.getProperties();
					std::cout << "Object has " << properties.size() << " properties" << std::endl;
					for (const auto& prop : properties)
					{
						std::cout << "Found property: " << prop.getName() << std::endl;
						std::cout << "Type: " << int(prop.getType()) << std::endl;
					}
				}
			}

			const auto& properties = layer->getProperties();
			std::cout << properties.size() << " Layer Properties:" << std::endl;
			for (const auto& prop : properties)
			{
				std::cout << "Found property: " << prop.getName() << std::endl;
				std::cout << "Type: " << int(prop.getType()) << std::endl;
			}
		}
	}
	std::cout << std::endl << "Press return to quit..." << std::endl;
}

void level3::loadDynamicMap()
{
	/// <summary>
	/// 	 BELOW LINE IS THE BLOCK LAYOUT FOR THE TUTORIAL LEVEL
	/// </summary>

	for (int i = 0; i < 10; i++)
	{
		blocks.push_back(new Block(m_world, "", 3000 + i * 64, 1650, 30)); //FAR STEPS (KEY PEDESTAL)
		blocks.push_back(new Block(m_world, "", 200 + i * 64, 950, 30)); //FAR STEPS (KEY PEDESTAL)
		blocks.push_back(new Block(m_world, "", 150 + i * 64, 900, 30)); //FAR STEPS (KEY PEDESTAL)
		blocks.push_back(new Block(m_world, "", 100 + i * 64, 840, 30)); //FAR STEPS (KEY PEDESTAL)
		blocks.push_back(new Block(m_world, "", 150 + i * 64, 900, 30)); //ROOF
		blocks.push_back(new Block(m_world, "", 400 + i * 64, 1000, 30)); ///FAR STEPS +1
		blocks.push_back(new Block(m_world, "", 3350 - i * 64, 1350, 30));
		blocks.push_back(new Block(m_world, "", 2700 + i * 64, 1500, 30)); //ROOF
		blocks.push_back(new Block(m_world, "", 3900 , 1500 - i * 64, 30)); //MIDDLE OF FLOOR ONE
		blocks.push_back(new Block(m_world, "", 600 + i * 64, 1400, 30)); //FAR STEPS (KEY PEDESTAL)
		blocks.push_back(new Block(m_world, "", 3600 + i * 64, 1500, 30)); //after steps
		//blocks.push_back(new Block(m_world, "", 600 + i * 64, 1600, 30)); ///LEFT HAND SIDE OF FLOOR ONE
	}



	for (int i = 0; i < 30; i++)
	{
			
			blocks.push_back(new Block(m_world, "", 600 + i * 64, 1600, 30)); //floor -1 
			blocks.push_back(new Block(m_world, "", 1200 + i * 64, 1200, 30)); //floor -1 
	}

	for (int i = 0; i < 40; i++)
	{
		//blocks.push_back(new Block(m_world, "", 600 + i * 64, 1600, 30)); //floor -1 
		blocks.push_back(new Block(m_world, "", 300 + i * 64, 1800, 30)); //floor -2 
		blocks.push_back(new Block(m_world, "", 300, 1700  - i * 64, 30)); //floor -1 left wall
	}

	for (int i = 0; i < 5; i++)
	{
		blocks.push_back(new Block(m_world, "", 2400, 1230 + i * 64, 30)); //RIGHT WALL floor -1
		blocks.push_back(new Block(m_world, "", 540, 1400 - i * 64, 30)); //Spawn point left wall
	//	blocks.push_back(new Block(m_world, "", 858, 1400 + i * 64, 30)); //LEFT WALL

	}
	//STEPS
	for (int i = 0; i < 2; i++)
	{
		blocks.push_back(new Block(m_world, "", 2950 + i * 64, 1650, 30));
		blocks.push_back(new Block(m_world, "", 2850 + i * 64, 1750, 30));
		blocks.push_back(new Block(m_world, "", 2900 + i * 64, 1700 , 30));

		blocks.push_back(new Block(m_world, "", 3450 + i * 64, 1600, 30));
		blocks.push_back(new Block(m_world, "", 3500 + i * 64, 1550, 30));
		blocks.push_back(new Block(m_world, "", 3550 + i * 64, 1500, 30));

		blocks.push_back(new Block(m_world, "", 2700 - i * 64, 1500, 30));
		blocks.push_back(new Block(m_world, "", 2650 - i * 64, 1450, 30));
		blocks.push_back(new Block(m_world, "", 2600 - i * 64, 1400, 30));
		blocks.push_back(new Block(m_world, "", 2520 - i * 64, 1350, 30));

		blocks.push_back(new Block(m_world, "", 1200 - i * 64, 1200, 30));
		blocks.push_back(new Block(m_world, "", 1150 - i * 64, 1150, 30));
		blocks.push_back(new Block(m_world, "", 1100 - i * 64, 1100, 30));
		blocks.push_back(new Block(m_world, "", 1050 - i * 64, 1050, 30));

		

	}
}

void level3::reset()
{
	crate->destroyBody();
	player = std::make_unique<Player>(m_world, "", 780, 1300, 30, false);
	crate = std::make_unique<Crate>(m_world, "", 3200, 200, 30);
	sphere = std::make_unique<Sphere>(m_world, "", 1030, 1250, 30);
	door = std::make_unique<Door>(m_world, "", 500, 730, 30);
	key = std::make_unique<Key>(m_world, 2710, 1720, 30);
	battery = std::make_unique<Battery>(m_world, 240, 750, 30);
	win = false;
}
