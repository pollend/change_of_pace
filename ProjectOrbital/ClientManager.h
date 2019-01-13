#pragma once
#include "Client.h"
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <list>
class ClientManager
{
private:
	std::list<sf::Packet*>* mPackets;

	int mClientID;
	sf::TcpSocket mSocket;
	void SocketListner();

	sf::Thread* mSocketListner;
sf::Mutex mPacketLock;
public:
	int getClientID(){return mClientID;}
	void SendToServer(sf::Packet* packet);
	sf::Packet* GetPacket(int PacketID);
	ClientManager(std::string IPAdress,unsigned short port);
	ClientManager();
	~ClientManager(void);
};

