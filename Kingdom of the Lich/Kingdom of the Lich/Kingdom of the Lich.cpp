//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>



////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Kingdom of the Lich");
	sf::RenderWindow *pWindow = &window;

	//create sf::View
	sf::View player_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	//Set it to be size of window
	player_view.setViewport(sf::FloatRect(0, 0, 1, 1));

	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	//Player* p = new Player();



	window.setFramerateLimit(60);

	sf::Sprite startup;
	sf::Texture startupTexture;
	startupTexture.loadFromFile("Assets/startScreenIcon.png");
	startup.setTexture(startupTexture);
	startup.setScale(sf::Vector2f(.5f, .5f));
	startup.setPosition(85, 260);

	//sf::Image icon;
	//icon.loadFromFile("Assets/icon2.png");
	//window.setIcon(32, 32, icon.getPixelsPtr());


	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();


		}

		

		//update sf::View center position
		//player_view.setCenter(p->getPosition());

		//set view of window to be player_view
		//window.setView(player_view);


		//prepare frame
		window.clear();
		//draw frame items
		//p->draw(*pWindow);
		window.draw(startup);

								 // Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}