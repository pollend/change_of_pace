#pragma once
#include <SFML\Network.hpp>
class TwoMessagePacket
{
private:
	std::string mMessage;
	sf::Packet* mPacket;
public:
	TwoMessagePacket(void);
	TwoMessagePacket(sf::Packet* Packet);
	TwoMessagePacket(std::string String);

	std::string getMessage(){return mMessage;}
	sf::Packet* getPacket(){return mPacket;}
	static int getPacketID(){return 2;}
	~TwoMessagePacket(void);
};

