#pragma once
#include <SFML\Network.hpp>
#include "ServerManager.h"
class ServerWaitingRoom
{
public:
	ServerWaitingRoom();
	ServerWaitingRoom(ServerManager* ServerManager, std::vector<Client*>* Players, short Port);
	~ServerWaitingRoom(void);

	void Update();
	bool IsPlayersAllReady();
	void StartListnerThread();
	void StopListnerThread();
private:
	int mNextID;

	void ListenForClients();

	ServerManager* mServerManager;
	std::vector<Client*>* mPlayers;

	sf::Thread* mListnerThread;
	sf::Mutex mMainLock;
	sf::TcpListener* mClientListner;
};

