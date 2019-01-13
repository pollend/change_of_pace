#include "GameScreen.h"
#include "SixKeyPressPacket.h"
#include "FivePlayerPacket.h"
#include "ScreenManager.h"
#include "ScoreScreen.h"
#include "InterfaceScreen.h"
GameScreen::GameScreen(void)
{
}
GameScreen::GameScreen(std::vector<Client*>* Playerlist,ClientManager* Client)
{
	SixKeyPressPacket::addKeyToKeyPressPacket(sf::Keyboard::W);
	SixKeyPressPacket::addKeyToKeyPressPacket(sf::Keyboard::A);
	SixKeyPressPacket::addKeyToKeyPressPacket(sf::Keyboard::S);
	SixKeyPressPacket::addKeyToKeyPressPacket(sf::Keyboard::D);

	mClients = Playerlist;
	mClientManager =Client;
	
	for(int x = 0; x < mClients->size(); x++)
	{
		mPlayers.push_back(Player((*mClients)[x]->GetClientID()));
	}
	mMap = new Map();

	while(!mMap->SyncWithServer(mClientManager));

	mGameTime = new sf::Clock();

	mLockGameScreen = false;
}


GameScreen::~GameScreen(void)
{
}

void GameScreen::Events(sf::Event Event)
{
}


void GameScreen::Load(ScreenManager* ScreenManager)
{
	ScreenManager->AddScreen(new InterfaceScreen());
}

void GameScreen::Update(ScreenManager* ScreenManager,sf::RenderWindow* Window,float DeltaT)
{
	//send key presses to the server to register
	if(!mLockGameScreen)
	{
		mClientManager->SendToServer(SixKeyPressPacket(sf::Keyboard::W,sf::Keyboard::isKeyPressed(sf::Keyboard::W)).getPacket());
		mClientManager->SendToServer(SixKeyPressPacket(sf::Keyboard::A,sf::Keyboard::isKeyPressed(sf::Keyboard::A)).getPacket());
		mClientManager->SendToServer(SixKeyPressPacket(sf::Keyboard::S,sf::Keyboard::isKeyPressed(sf::Keyboard::S)).getPacket());
		mClientManager->SendToServer(SixKeyPressPacket(sf::Keyboard::D,sf::Keyboard::isKeyPressed(sf::Keyboard::D)).getPacket());
	}
	//used to sync the players Location from the server
	sf::Packet* lPlayerPacket = mClientManager->GetPacket(FivePlayerPacket::getPacketID());
	while(lPlayerPacket != NULL)
	{
		FivePlayerPacket lPlayerData(lPlayerPacket);
		for(int x = 0; x < mPlayers.size(); x++)
		{
			mPlayers[x].SyncFromServer(lPlayerData);
		}
		 lPlayerPacket = mClientManager->GetPacket(FivePlayerPacket::getPacketID());
	}

	for(int x = 0; x < mPlayers.size(); x++)
	{
		mPlayers[x].Update(DeltaT,mMap);
		if(mPlayers[x].EndPointIntersection(mMap) != -1)
		{
			if(mPlayers[x].EndPointIntersection(mMap) == mClientManager->getClientID())
			{
				mLockGameScreen = true;
				ScreenManager->AddScreen(new ScoreScreen(mClientManager));
			}
			mPlayers.erase(mPlayers.begin() + x);
			x--;
		}
	}
	
	mMap->Update(DeltaT,mGameTime);
}

void GameScreen::Draw(sf::RenderWindow* Window)
{

	if(mLockGameScreen)
	{
		if(mPlayers.size() > 0)
		{
			mPlayers[mPlayers.size()-1].Camera(Window);
		}
	}
	else
	{
		for(int x = 0; x < mPlayers.size(); x++)
		{
			if(mPlayers[x].getClientID() == mClientManager->getClientID())
			{
				mPlayers[x].Camera(Window);
			}
		}
	}
	mMap->Draw(Window);

	for(int x = 0; x < mPlayers.size(); x++)
	{
		mPlayers[x].Draw(Window);
	}
}

