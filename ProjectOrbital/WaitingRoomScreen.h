#pragma once
#include "IScreen.h"
#include "ServerManager.h"
#include "ClientManager.h"
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "TextEntry.h"
#include "Btn.h"
void ListnerThread();

class WaitingRoomScreen : public IScreen
{
private:

	ClientManager* mClient;
	//Player List
	std::vector<Client*>* mPlayers;
	//Text entry and messages
	std::vector<std::string> mMessages;
	TextEntry mTextEntry;
	sf::Text mText;

	Btn mReadyButton;

public:
	WaitingRoomScreen();
	WaitingRoomScreen(std::string IPAdress,unsigned short port,bool IsServer) ;
	~WaitingRoomScreen(void);

	virtual void Load(ScreenManager* ScreenManager);
	virtual void Update(ScreenManager* ScreenManager,sf::RenderWindow* Window,float DeltaT);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void Events(sf::Event Event);
	virtual bool Opaque(){return false;}
	virtual bool BlockUpdate(){return false;}
};

