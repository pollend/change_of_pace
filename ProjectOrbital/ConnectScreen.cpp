#include "ConnectScreen.h"
#include "ScreenManager.h"
#include "WaitingRoomScreen.h"
#include "TextureManager.h"
ConnectScreen::ConnectScreen(void)
{
	mMap.Generate(1280,NULL);
	mTime = new sf::Clock();
}


ConnectScreen::~ConnectScreen(void)
{
	delete mTime;
}
	
void ConnectScreen::Load(ScreenManager* ScreenManager)
{
	mClientButton = Btn("Assets//MainMenu//ConnectScreen//client.png");
	mServerButton =Btn("Assets//MainMenu//ConnectScreen//Server.png");
	mTitleSprite.setTexture(*TextureManager::LoadAndRetrieveTexture("Assets//MainMenu.png"));
	mTitleSprite.setPosition(0,0);
	
	mClientButton.SetPosition(sf::Vector2f(1280/2 - (mClientButton.getSize().x/2),400));
	mServerButton.SetPosition(sf::Vector2f(1280/2- (mServerButton.getSize().x/2),300));

	mIP = TextEntry(1280/2 - (200/2),500,200);
}

void ConnectScreen::Update(ScreenManager* ScreenManager,sf::RenderWindow* Window,float DeltaT)
{
	if(mClientButton.IsButtonPressedAndReleased(Window))
	{
		ScreenManager->PopAllScreens();
		ScreenManager->AddScreen(new WaitingRoomScreen(	mIP.getString(),3979,false));
	}
	if(mServerButton.IsButtonPressedAndReleased(Window))
	{
		ScreenManager->PopAllScreens();
		ScreenManager->AddScreen(new WaitingRoomScreen(	mIP.getString(),3979,true));
	}
	mMap.Update(DeltaT,mTime);

}

void ConnectScreen::Draw(sf::RenderWindow* Window)
{
		mMap.Draw(Window);
		Window->draw(mTitleSprite);
	mClientButton.Draw(Window);
	mServerButton.Draw(Window);
	mIP.Draw(Window);

}

void ConnectScreen::Events(sf::Event Event)
{
		mIP.Event(Event);
}