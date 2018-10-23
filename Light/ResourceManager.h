#pragma once

#include <Thor\Resources.hpp>
#include <SFML\Graphics.hpp>
#include<SFML\Audio.hpp>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	thor::ResourceHolder<sf::Texture, std::string> m_textureHolder;	//Resource manager to hold textures
	thor::ResourceHolder<sf::Font, std::string> m_fontHolder;		//Resource manager to hold fonts
	thor::ResourceHolder<sf::SoundBuffer, std::string> m_songHolder; //Resource manager to hold music
	thor::ResourceHolder<sf::Shader, std::string> m_shaderHolder;   //Resource manager to hold shaders
};
