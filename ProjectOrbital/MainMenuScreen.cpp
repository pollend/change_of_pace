#include "MainMenuScreen.h"
#include "Btn.h"
#include <SFML\Graphics.hpp>
#include "TextureManager.h"

MainMenuScreen::MainMenuScreen(void)
{
	mTestEntry = TextEntry(10,10,100);
	mStuff.setTexture(*TextureManager::LoadAndRetrieveTexture("Assets//Cloud.png"));
}


MainMenuScreen::~MainMenuScreen(void)
{
}

void MainMenuScreen::Load(ScreenManager* ScreenManager)
{
}

 void MainMenuScreen::Events(sf::Event Event)
 {
	 mTestEntry.Event(Event);
 }

void MainMenuScreen::Update(ScreenManager* ScreenManager,sf::RenderWindow* Window,float DeltaT)
{


}

void MainMenuScreen::Draw(sf::RenderWindow* Window)
{
	mTestEntry.Draw(Window);
	Window->draw(mStuff);

}

