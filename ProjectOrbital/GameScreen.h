#pragma once
#include "IScreen.h"
#include "Client.h"
#include "Server.h"
#include "ServerManager.h"
#include "ClientManager.h"
#include "Map.h"
#include "Player.h"
class GameScreen : public IScreen
{
public:
	GameScreen(void);
	GameScreen(std::vector<Client*>* Clients,ClientManager* Client);
	~GameScreen(void);

	virtual void Load(ScreenManager* ScreenManager);
	virtual void Update(ScreenManager* ScreenManager,sf::RenderWindow* Window,float DeltaT);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void Events(sf::Event Event);
	virtual bool Opaque(){return false;}
	virtual bool BlockUpdate(){return false;}
private:
	bool mLockGameScreen;
	std::vector<Client*>* mClients;
	std::vector<Player> mPlayers;
	ClientManager* mClientManager;
	sf::View mCamera;
	Map* mMap;
	sf::Clock* mGameTime;
};

