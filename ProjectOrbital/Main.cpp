
#include <iostream>
#include <SFML\Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ScreenManager.h"
#include "MainMenuScreen.h"
#include "ConnectScreen.h"
#define SCREEN_WIDTH	1280
#define SCREEN_HEIGHT	720
#define BITS_PER_PIXEL	32

void DisplayFPS(int& numFrames, sf::Time& elapsedTime, sf::Time& fpsTime);

int main()
{
	

	

	sf::RenderWindow* Window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BITS_PER_PIXEL), "A Change of Pace");

	// used to compute fps
	sf::Clock clock;
	sf::Time lElapsedTime = clock.getElapsedTime();
	sf::Time fpsTime = clock.getElapsedTime();				
	int numFrames = 0;


	ScreenManager*screenManager = new ScreenManager();
	screenManager->AddScreen(new ConnectScreen());


	 while (Window->isOpen())
	{
		sf::Event Event;

		while (Window->pollEvent(Event))
		{
			//update the events all attached to the screen
			screenManager->UpdateEventsForScreens(Event);

			switch (Event.type)
			{
			case sf::Event::Closed:
				Window->close();
				break;

			default:
				break;
			}
		}

		float lFrameTime = clock.getElapsedTime().asSeconds() - lElapsedTime.asSeconds();
		lElapsedTime = clock.getElapsedTime();

		DisplayFPS(numFrames, lElapsedTime, fpsTime);
		if(lFrameTime >1)
		lFrameTime =0;
		screenManager->Update(Window, lFrameTime);

		//draws the screen manager
		Window->clear();
		screenManager->Draw(Window);
		Window->display();
		

	}

	delete screenManager;
	delete Window;

	
	screenManager = 0;
	Window = 0;

	return 0;
}

void DisplayFPS(int& numFrames, sf::Time& elapsedTime, sf::Time& fpsTime)
{
	// Calculate/Display FPS
	numFrames++;
	if (elapsedTime.asSeconds() >= fpsTime.asSeconds() + 1.0f) 
	{
		std::cout << "fps = " << numFrames << "\n";
		fpsTime = elapsedTime;
		numFrames = 0;
	}
}