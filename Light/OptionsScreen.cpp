#include "OptionsScreen.h"

OptionsScreen::OptionsScreen(Game & game) :
	m_game(&game)
{
	m_manager = std::make_unique<ResourceManager>();
	m_controllerTexture = m_manager->m_textureHolder["control"];
	m_keyTexture = m_manager->m_textureHolder["key"];
	m_batteryTexture = m_manager->m_textureHolder["battery"];
	m_doorTexture = m_manager->m_textureHolder["door"];
	m_crateTexture = m_manager->m_textureHolder["crate"];
	m_ballTexture = m_manager->m_textureHolder["ball"];

	m_title = new Label("Options", m_game->m_window.getSize().x / 4, 0);
	m_gui.addLabel(m_title);
	m_help = new Button("Help", 200, 700);
	m_help->Enter = std::bind(&OptionsScreen::helpScreen, this);
	m_Back = new Button("Back", 200, 900);
	m_Back->Enter = std::bind(&OptionsScreen::goMain, this);
	m_volume = new Slider(200.0f, 200.0f, 100.0f, std::string("Music"));
	m_volume->getFocus();
	m_music = new CheckBox("Music ( On/Off )", 200.0f, 250.0f);
	m_music->getActive();

	m_gui.addSlider(m_volume);
	m_gui.addCheckBox(m_music);
	m_gui.addButton(m_help);
	m_gui.addButton(m_Back);

	m_optBack = new Button("Back", 200, 900);
	m_optBack->Enter = std::bind(&OptionsScreen::mainOptScreen, this);
	m_optBack->getFocus();
	m_helptitle = new Label("Help", m_game->m_window.getSize().x / 5, 0);
	m_guiHelp.addLabel(m_helptitle);
	m_controls = new Label("Controls", m_game->m_window.getSize().x / 3, m_game->m_window.getSize().y / 16);
	m_guiHelp.addLabel(m_controls);
	m_objects = new Label("Game Objects", 100, 100);
	m_guiHelp.addLabel(m_objects);
	m_key = new Label("Key [Unlocks the door]", 325, 425);
	m_guiHelp.addLabel(m_key);
	m_door = new Label("Door [Opens to procced to next level]", 225, 275);
	m_guiHelp.addLabel(m_door);
	m_battery = new Label("Battery [Collect to recharge torch]", 300, 525);
	m_guiHelp.addLabel(m_battery);
	m_crate = new Label("Crate [Can be pushed by player]", 250, 680);
	m_guiHelp.addLabel(m_crate);

	m_ball = new Label("Ball [Collect to finish the game]", 250, 800);
	m_guiHelp.addLabel(m_ball);

	m_guiHelp.addButton(m_optBack);

	m_currentSelect = 0;
	m_gui.vertical = true;
	m_guiHelp.vertical = true;
	m_title->changeTextSize(100);

	controller.setTexture(m_controllerTexture);
	controller.setPosition(m_game->m_window.getSize().x / 4, m_game->m_window.getSize().y / 10);
	controller.setScale(3, 3);

	key.setTexture(m_keyTexture);
	key.setPosition(100, 400);
	key.setScale(1, 1);
	m_key->changeTextSize(40);
	m_key->m_text.setFillColor(sf::Color::Red);

	battery.setTexture(m_batteryTexture);
	battery.setPosition(100, 450);
	battery.setScale(1, 1);
	m_battery->changeTextSize(40);
	m_battery->m_text.setFillColor(sf::Color::Red);

	door.setTexture(m_doorTexture);
	door.setPosition(100, 250);
	door.setScale(1, 1);
	m_door->changeTextSize(40);
	m_door->m_text.setFillColor(sf::Color::Red);

	crate.setTexture(m_crateTexture);
	crate.setPosition(100, 630);
	crate.setScale(2, 2);
	m_crate->changeTextSize(40);
	m_crate->m_text.setFillColor(sf::Color::Red);

	ball.setTexture(m_ballTexture);
	ball.setPosition(100, 780);
	ball.setScale(2, 2);
	m_ball->changeTextSize(40);
	m_ball->m_text.setFillColor(sf::Color::Red);

}

OptionsScreen::~OptionsScreen()
{
}

void OptionsScreen::render(sf::RenderWindow & window)
{
	if (help)
	{
		m_guiHelp.draw(window);
		window.draw(controller);
		window.draw(key);
		window.draw(battery);
		window.draw(door);
		window.draw(crate);
		window.draw(ball);
	}
	else
	{
		m_gui.draw(window);
	}
}

void OptionsScreen::update()
{
	if (!help)
	{
		m_gui.update(m_currentSelect, 4);
		m_game->music.setVolume(m_volume->getValue());
		if (!m_music->checkActive() && m_game->music.getStatus() == sf::Sound::SoundSource::Playing) {
			m_game->music.pause();
		}
		else if (m_music->checkActive())
		{
			if (m_game->music.getStatus() == sf::Sound::SoundSource::Paused)
			{
				m_game->music.play();
			}
		}
	}
	else
	{

		m_guiHelp.update(m_currentSelect, 1);
	}
}

void OptionsScreen::goMain()
{
	m_game->changeGameStates(GameStates::Menu);
}

void OptionsScreen::mainOptScreen()
{
	help = false;
	mainOpt = true;
	m_currentSelect = 2;
}

void OptionsScreen::helpScreen()
{
	mainOpt = false;
	help = true;
	m_currentSelect = 0;
}

