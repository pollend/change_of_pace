#pragma once
#include <vector>
#include "Client.h"
#include"ServerManager.h"
#include <SFML\Network.hpp>
#include "ServerWaitingRoom.h"
#include "ServerGameScreen.h"
class Server
{
private:
	enum ServerState{
		WAITING_ROOM,
		GAME_SCREEN
	};

	ServerState mServerState;
	std::vector<Client*>* mPlayers;
	ServerManager* mServerManager;
	sf::Thread* mMainThread;
	
	ServerWaitingRoom* mServerWaitingRoom;
	ServerGameScreen* mServerGameScreen;

	//the main server thread
	void ServerMain();
	//Kill the server and delete everything
	void KillServer();
public:
	Server(short Port);
	~Server(void);
};

