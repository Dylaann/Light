#include "Level1.h"


level1::level1(Game &game) : m_gravity{ 0, 100 },
	m_world{ m_gravity }, m_game(&game )
{
//	loadMap();
	loadDynamicMap();
	view1.setSize(sf::Vector2f(1920, 1080));
	view1.zoom(0.6f);

	playerTexture.loadFromFile("spriteSheet4.png");
	levelOneT.loadFromFile("ASSETS/IMAGES/level1.png");


	bg.setTexture(levelOneT);
	bg.setOrigin(680, 0);

	player = std::make_unique<Player>(m_world, "", 190, 730, 30, false);

	textureSize = playerTexture.getSize();
	textureSize.x /= 22;
	textureSize.y /= 1;
	crate = std::make_unique<Crate>(m_world, "", 1300, 720, 30);
	door = std::make_unique<Door>(m_world, "", 500, 730, 30);
	key = std::make_unique<Key>(m_world, 1810, 620, 30);
	battery = std::make_unique<Battery>(m_world, 170, 780, 30);

	m_startText = new Label("I need to find \n my football", 190, 640);
	m_gui.addLabel(m_displayText);
	m_startText->changeTextSize(20);
	
	m_keyIconT.loadFromFile("ASSETS\\IMAGES\\keyPickup.png");
	m_keyIcon.setTexture(m_keyIconT);
	m_keyIcon.setPosition(player->getPosition().x, player->getPosition().y);
	m_keyIcon.setScale(0.5, 0.5);

	m_pillarT.loadFromFile("ASSETS\\IMAGES\\pillar.png");
	m_pillar.setTexture(m_pillarT);
	m_pillar.setPosition(1180, 550);

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


void level1::update(float deltaTime) {
	m_world.Step(1 / 60.f, 10, 5);
	crate->Update();
	door->Update();
	battery->update();
	player->Update(deltaTime, view1);
	m_xbox.update();
	

	if (player->getPosition().x >= 10)
	{
		set = false;
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


	crate->Update();

	if (player->getPosition().x < battery->getPosition().x)
	{
		player->m_battery = 0;
		battery->collected = true;
		battery->destroyBody();
	}

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
			reset();
			goMenu();
		}
	}
	
	if (key->collected == false) {
		key->update(deltaTime);
	}
	else
	{
		m_keyIcon.setPosition(player->getPosition().x * 30 + 500, player->getPosition().y* 30 - 260);
	}
	
}


void level1::draw(sf::RenderWindow &window) {
	window.setView(view1);
	//window.draw(*map1.at(0));
	//sf::RenderWindow(levelOneT);
	window.draw(bg);
	window.draw(m_pillar);
	//window.draw(*map1.at(0));
	

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
	
	if(key->collected == false)
	{
		m_displayText->draw(window);
		m_crateText->draw(window);
	}
	
	if (set == true )
	{
		m_startText->draw(window);
	}
	

	key->render(window);
	
	if (win == true)
	{
		m_goalText->draw(window);
	}
	door->Draw(window);
	crate->Draw(window);
	battery->render(window);
	
	if (key->collected == true)
	{
		m_collectedText->draw(window);
		
		std::cout << "PosX: " << m_keyIcon.getPosition().x << "PosY: " << m_keyIcon.getPosition().y << std::endl;

	}
	player->Draw(window);
	
	if (key->collected == true)
	{
		window.draw(m_keyIcon);
	}
}

void level1::goMenu()
{
	player->m_body->SetTransform(b2Vec2(580 / 30, 720 / 30), 0);
	player->m_battery = 0;
	win = false;
	m_game->m_gameOver->level1Complete = true;
	m_game->changeGameStates(GameStates::levelComplete);
}

void level1::loadMap()
{
	if (map.load("maps/map3.tmx"))
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

void level1::loadDynamicMap()
{
	/// <summary>
	/// 	 BELOW LINE IS THE BLOCK LAYOUT FOR THE TUTORIAL LEVEL
	/// </summary>

	for (int i = 0; i < 40; i++)
	{
		blocks.push_back(new Block(m_world, "", 1700 +i * 64, 720 , 30)); //FAR STEPS (KEY PEDESTAL)
		blocks.push_back(new Block(m_world, "", 1700 + i * 64, 780, 30)); ///FAR STEPS +1
		blocks.push_back(new Block(m_world, "", 170 + i * 64, 520, 30)); //ROOF
		blocks.push_back(new Block(m_world, "", 170 + i * 64, 840, 30)); //MIDDLE OF FLOOR ONE
		blocks.push_back(new Block(m_world, "", 1880 + i * 64, 570, 30)); //RIGHT WALL
		blocks.push_back(new Block(m_world, "", 1880 + i * 64, 660 , 30)); ///LEFT HAND SIDE OF FLOOR ONE
	}

	for (int i = 0; i < 6; i++)
	{
		blocks.push_back(new Block(m_world, "", 120, 840 - i * 64, 30)); //LEFT WALL
		blocks.push_back(new Block(m_world, "", 55, 840 - i * 64, 30)); //LEFT WALL
		
	}
}

void level1::reset()
{
	crate->destroyBody();
	player = std::make_unique<Player>(m_world, "", 280, 730, 30, false);
	crate = std::make_unique<Crate>(m_world, "", 1300, 720, 30);
	door = std::make_unique<Door>(m_world, "", 500, 730, 30);
	key = std::make_unique<Key>(m_world, 1810, 620, 30);
	battery = std::make_unique<Battery>(m_world, 280, 750, 30);
	win = false;

}
