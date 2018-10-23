/// <summary>
/// @author Dylan Murphy & David O'Gorman
/// @date October 2017 - Due Date
/// </summary>


#include "Game.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"Box2D.lib")
#pragma comment(lib, "thor-d.lib")
#pragma comment(lib,"libtmxlite-s-d.lib")
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#pragma comment(lib,"Box2D.lib")
#pragma comment(lib, "thor.lib")
#pragma comment(lib,"libtmxlite.lib")
#endif 

int main()
{
	Game game;
	game.run();

	return 1;
}