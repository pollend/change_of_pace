#include "WaitingRoomScreen.h"
#include <iostream>
#include "OneClientPacket.h"
#include "TwoMessagePacket.h"
#include "Server.h"
#include <sstream>  
#include "ThreeIsReadyPacket.h"
#include "ScreenManager.h"
#include "GameScreen.h"

WaitingRoomScreen::WaitingRoomScreen()
{

}

WaitingRoomScreen::WaitingRoomScreen(std::string IPAdress,unsigned short port,bool IsServer)
{

	mTextEntry = TextEntry(.10*1280,.90 * 720,.65 *1280);

	//list of clients
	mPlayers = new std::vector<Client*>();
	if(IsServer)
		new Server(port);
	//create a client socket and connect to the server itself
	mClient = new ClientManager(IPAdress,port);

	//LOAD UI
	mText.setCharacterSize(20);

}

WaitingRoomScreen::~WaitingRoomScreen(void)
{
	
}


void WaitingRoomScreen::Load(ScreenManager* ScreenManager)
{
	mReadyButton = Btn("Assets//MainMenu//WaitingScreen//Ready.png");
}
void WaitingRoomScreen::Update(ScreenManager* ScreenManager,sf::RenderWindow* Window,float DeltaT)
{
	//send a ready message to the server
	if(mReadyButton.IsButtonPressedAndReleased(Window))
	{
		mClient->SendToServer(ThreeIsReadyPacket(true).getPacket());
	}
	sf::Packet* lReadyPacket = mClient->GetPacket(3);
	if(lReadyPacket != NULL)
	{
		ThreeIsReadyPacket lReady = ThreeIsReadyPacket(lReadyPacket);
		for(int x = 0; x < mPlayers->size(); x++)
		{
			if((*mPlayers)[x]->GetClientID() == lReady.getPlayerID())
			{
				(*mPlayers)[x]->setIsReadyState(lReady.getReadyState());
			}
		}
	}

	bool lSwitchScreen = true;
	if(mPlayers->size() > 0)
	{
		for(int x = 0; x < mPlayers->size(); x++)
		{
			if(!(*mPlayers)[x]->getReadyState())
			{
				lSwitchScreen = false;
				break;
			}
		}
		if(lSwitchScreen)
		{
			ScreenManager->PopAllScreens();
			ScreenManager->AddScreen(new GameScreen(mPlayers,mClient));
		}
	}



	sf::Packet* lPacket = mClient->GetPacket(1);
	if(lPacket != NULL)
	{
		Client* lClient = OneClientPacket(lPacket).GetClient();
		mPlayers->push_back(lClient);
	}

	sf::Packet* lMessagePacket = mClient->GetPacket(2);
	if(lMessagePacket != NULL)
	{
		std::string lMessage = TwoMessagePacket(lMessagePacket).getMessage();
		mMessages.push_back(lMessage);
	}


	//send the message to the server
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		std::string lString  =mTextEntry.getString();
		if(lString != "")
		{
		sf::Packet* lPacket = TwoMessagePacket(lString).getPacket();
		mClient->SendToServer(lPacket);
		mTextEntry.Clear();
		}
	}

}
void WaitingRoomScreen::Draw(sf::RenderWindow* Window)
{
	for(int x= 0; x < mPlayers->size(); x++)
	{
		std::ostringstream lPlayerString ;
		lPlayerString << "player" << x << "          " << ((*mPlayers)[x]->getReadyState() ? "READY" : "NOT READY");
		mText.setString(lPlayerString.str());
		mText.setPosition(1280*.75f,(x*20)+(720*.20f));
		Window->draw(mText);
	}
	for (int x = 0; x < mMessages.size(); x++) {
		mText.setString(mMessages[ mMessages.size() - 1-x]);
		mText.setPosition(0,(.90*720) - (x *20));
		Window->draw(mText);
	}
	mReadyButton.Draw(Window);
	mTextEntry.Draw(Window);
}
void WaitingRoomScreen::Events(sf::Event Event)
{
	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		mTextEntry.Event(Event);
	}
}