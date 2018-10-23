#include "Level2.h"


level2::level2(Game &game) : m_gravity{ 0, 100 },
m_world{ m_gravity }, m_game(&game)
{

	//loadMap();
	loadDynamicMap();
	view1.setSize(sf::Vector2f(1920, 1080));
	view1.zoom(0.6f);

	playerTexture.loadFromFile("spriteSheet4.png");
	levelTwoT.loadFromFile("ASSETS/IMAGES/levle2.png");

	

	bg2.setTexture(levelTwoT);
	bg2.setOrigin(250, 200);

	player = std::make_unique<Player>(m_world, "", 780, 730, 30, false);
	textureSize = playerTexture.getSize();
	textureSize.x /= 22;
	textureSize.y /= 1;
	crate = std::make_unique<Crate>(m_world, "", 1060, 720, 30);
	crate2 = std::make_unique<Crate>(m_world, "", 2000, 720, 30);
	crate3 = std::make_unique<Crate>(m_world, "", 2000, 200, 30);
	door = std::make_unique<Door>(m_world, "", 500, 230, 30);
	key = std::make_unique<Key>(m_world, 3100, 140, 30);
	battery = std::make_unique<Battery>(m_world, 2300, 630, 30);
	m_keyIconT.loadFromFile("ASSETS\\IMAGES\\keyPickup.png");
	m_keyIcon.setTexture(m_keyIconT);
	m_keyIcon.setPosition(player->getPosition().x, player->getPosition().y);
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
}

void level2::update(float deltaTime) {
	m_world.Step(1 / 60.f, 10, 5);
	crate->Update();
	crate2->Update();
	crate3->Update();
	door->Update();
	battery->update();
	player->Update(deltaTime, view1);
	m_xbox.update();

	if (player->getPosition().x + 4 >= battery->getPosition().x && battery->collected == false)
	{
		player->m_battery = 0;
		battery->collected = true;
		battery->m_keySound.play();
		

	}

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
	

	if (player->getPosition().x >= battery->getPosition().x &&  battery->collected == false)
	{
		player->m_battery = 0;
		battery->collected = true;
	//	battery->m_keySound.play();
		battery->destroyBody();
	}

	std::cout << player->getPosition().x << std::endl;
	if (key->collected == true && player->getPosition().x <= 17 && player->getPosition().x >= 14)
	{

		if (m_xbox.m_currentState.X || sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			player->m_battery = 0;
			view1.reset(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1920, 1080)));
			view1.zoom(0.6f);
			std::cout << "Pressed" << std::endl;
			door->m_doorSound.play();
			win = true;
			m_game->m_gameOver->level2Complete = true;
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

}


void level2::draw(sf::RenderWindow &window) {
	window.setView(view1);
//	window.draw(*map1.at(0));
	window.draw(bg2);

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
		//m_displayText->draw(window);
		//m_crateText->draw(window);
	}

	key->render(window);

	door->Draw(window);
	crate->Draw(window);
	crate2->Draw(window);
	crate3->Draw(window);
	battery->render(window);
	player->Draw(window);

	if (win == true)
	{
		m_goalText->draw(window);
	}

	

	if (key->collected == true)
	{
		//m_collectedText->draw(window);
		window.draw(m_keyIcon);
		std::cout << "PosX: " << m_keyIcon.getPosition().x << "PosY: " << m_keyIcon.getPosition().y << std::endl;

	}


}

void level2::goMenu()
{
	player->m_body->SetTransform(b2Vec2(580 / 30, 720 / 30), 0);
	player->m_battery = 0;
	reset();
	m_game->changeGameStates(GameStates::levelComplete);

}

void level2::loadMap()
{
	if (map.load("maps/map4.tmx"))
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
	else
	{
		std::cout << "Failed loading map" << std::endl;
	}
	std::cout << std::endl << "Press return to quit..." << std::endl;
}

void level2::loadDynamicMap()
{
	/// <summary>
	/// 	 BELOW LINE IS THE BLOCK LAYOUT FOR THE TUTORIAL LEVEL
	/// </summary>

	for (int i = 0; i < 40; i++)
	{
		//Steps
	//
		blocks.push_back(new Block(m_world, "", 1700 + i * 64, 800, 30)); 
		blocks.push_back(new Block(m_world, "", 1300 + i * 64, 30, 30));
                                                                                                                             

		blocks.push_back(new Block(m_world, "", 170 + i * 64, 840, 30)); //MIDDLE OF FLOOR ONE
	//	blocks.push_back(new Block(m_world, "", 2500 , 570 - i * 64, 30)); //RIGHT WALL
		blocks.push_back(new Block(m_world, "", 1880 + i * 64, 860, 30)); ///LEFT HAND SIDE OF FLOOR ONE
	}

	for (int i = 0; i < 9; i++)
	{
		blocks.push_back(new Block(m_world, "", 2800, 760 - i * 64, 30));
	}

	for (int i = 0; i < 6; i++)
	{
		blocks.push_back(new Block(m_world, "", 280, 610 - i * 64, 30)); //Right wall
		blocks.push_back(new Block(m_world, "", 280, 810 - i * 64, 30)); //Right wall
	}

	for (int i = 0; i < 6; i++)
	{
	//	blocks.push_back(new Block(m_world, "", 2550, 610 - i * 64, 30)); //Right wall
		blocks.push_back(new Block(m_world, "", 2000 + i * 64, 270, 30)); //ROOF
		blocks.push_back(new Block(m_world, "", 1200 + i * 64, 270, 30)); //ROOF
		blocks.push_back(new Block(m_world, "", 2000 - i * 64, 400, 30)); //ROOF

	}

	for (int i = 0; i < 6; i++)
	{
		blocks.push_back(new Block(m_world, "", 2550, 610 - i * 64, 30)); //Right wall
		
	}

	for (int i = 0; i < 6; i++)
	{
		blocks.push_back(new Block(m_world, "", 2860 + i * 64, 240, 30)); //Key place		
		blocks.push_back(new Block(m_world, "", 3200 , 250 - i * 64, 30)); //Key pLACRE WALL

	}

	for (int i = 0; i < 2; i++)
	{
		blocks.push_back(new Block(m_world, "", 2750 + i * 64, 735, 30)); 		
		blocks.push_back(new Block(m_world, "", 1960 + i * 64, 370, 30));


	}
	

		//block one
	for (int i = 0; i < 4; i++)
	{
		blocks.push_back(new Block(m_world, "", 1120, 890 - i * 64, 30)); //LEFT WALL
		blocks.push_back(new Block(m_world, "", 1180, 830 - i * 64, 30)); //LEFT WALL
		blocks.push_back(new Block(m_world, "", 2000, 270 + i * 64, 30)); //ROOF
		blocks.push_back(new Block(m_world, "", 1600, 270 + i * 64, 30)); //ROOF

	}

	blocks.push_back(new Block(m_world, "", 2740, 670, 30)); //blockstep1
	blocks.push_back(new Block(m_world, "", 2600, 590, 30)); //blockstep2
	blocks.push_back(new Block(m_world, "", 2740, 510, 30)); //blockstep3
	blocks.push_back(new Block(m_world, "", 2600, 430, 30)); //blockstep4
	blocks.push_back(new Block(m_world, "", 2740, 360, 30)); //blockstep5
}

void level2::reset()
{
	crate->destroyBody();
	crate2->destroyBody();
	crate3->destroyBody();
	player = std::make_unique<Player>(m_world, "", 780, 730, 30, false);
	crate = std::make_unique<Crate>(m_world, "", 1000, 720, 30);
	crate2 = std::make_unique<Crate>(m_world, "", 2000, 720, 30);
	crate3 = std::make_unique<Crate>(m_world, "", 2000, 200, 30);
	door = std::make_unique<Door>(m_world, "", 500, 230, 30);
	key = std::make_unique<Key>(m_world, 2010, 620, 30);
	battery = std::make_unique<Battery>(m_world, 280, 750, 30);
	win = false;
}
