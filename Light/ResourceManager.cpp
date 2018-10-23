#include "ResourceManager.h"
/// <summary>
/// @Author Dylan Murphy
/// @Version 1.0
/// </summary>

ResourceManager::ResourceManager()
{
	// Textures
	m_textureHolder.acquire("control", thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\controller.png"));
	m_textureHolder.acquire("key", thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\key.png"));
	m_textureHolder.acquire("battery", thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\battery.png"));
	m_textureHolder.acquire("ball", thor::Resources::fromFile<sf::Texture>("ASSETS\\IMAGES\\football2.png"));
	m_textureHolder.acquire("crate", thor::Resources::fromFile<sf::Texture>("crate.png"));
	m_textureHolder.acquire("door", thor::Resources::fromFile<sf::Texture>("doorT.png"));
	
	// Fonts
	m_fontHolder.acquire("pap", thor::Resources::fromFile<sf::Font>("ASSETS\\FONTS\\PAPYRUS.ttf"));
	m_fontHolder.acquire("ari", thor::Resources::fromFile<sf::Font>("ASSETS\\FONTS\\ariblk.ttf"));

	// Music
	m_songHolder.acquire("music", thor::Resources::fromFile<sf::SoundBuffer>("ASSETS\\SOUNDS\\music.wav"));
}

ResourceManager::~ResourceManager()
{
}