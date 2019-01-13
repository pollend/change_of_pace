#pragma once
#include <SFML\Network.hpp>
#include <list>
class ServerSocket
{
private:
	sf::TcpSocket* mClientSocket;
	sf::Thread* mSocketListner;
	sf::Mutex mPacketLock;
	std::list<sf::Packet*>* mPackets;
	void SocketListner();
public:

	sf::Packet* GetPacket(int ID);
	void SendPacket(sf::Packet* Packet);
	ServerSocket(sf::TcpSocket* Socket);
	ServerSocket(void);
	~ServerSocket(void);
};

