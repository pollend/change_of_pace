#pragma once
#include <map>
#include "Client.h"
#include <SFML\Network.hpp>
#include <list>
#include "ServerSocket.h"
class ServerManager
{
protected:

private:


	std::map<int,ServerSocket*> mSockets;
	int mStoredPackets;
	sf::Mutex mSocketLock;

public:
	ServerManager(void);
	~ServerManager(void);
	//Add client and push the socket
	void AddClient(Client* Client,sf::TcpSocket* Socket);
	//send to all the clients in the set
	void SendToAllClients(sf::Packet* Packet);
	//send to all the client excpet one client
	void SendToAllClientsExcept(sf::Packet* Packet,Client* client);
	//send to single Client
	void SendToClient(sf::Packet* Packet,Client* client);
	//get packets
	sf::Packet* GetPackets(Client* client,int ID);
	sf::Packet* GetPackets(int ClientID,int ID);

};

