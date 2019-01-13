#pragma once
#include "Client.h"
#include <SFML\Network.hpp>
class OneClientPacket 
{
private:
	sf::Packet* mPacket;
	Client* mClient;
public:
	OneClientPacket(sf::Packet* Packet);
	OneClientPacket(Client* Client);
	~OneClientPacket(void);

	static int getPacketID(){return 1;}

	Client* GetClient(){return mClient;}
	sf::Packet* getPacket(){return mPacket;}

};

