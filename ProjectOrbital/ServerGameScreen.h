#pragma once
#include <SFML\Network.hpp>
#include "ServerManager.h"
#include "Map.h"
#include "Player.h"
#include "SevenScorePacket.h"
#include "ScoreObject.h"
class ServerGameScreen
{
private:
	Map* mMap;
	std::vector<Client*>* mClients;
	std::vector<Player> mPlayers;
	//score items
	std::vector<Client*> mScore;
	std::vector<ScoreObject> mScoreObject;
	// used to compute fps
	sf::Clock mFrameRate;
	sf::Clock* mGameTime;
	sf::Time mElapsedTime;

public:
	ServerGameScreen(ServerManager* ServerManager,std::vector<Client*>* Players);
	~ServerGameScreen(void);

	void ServerGameScreen::Update(ServerManager* ServerManager);
};

