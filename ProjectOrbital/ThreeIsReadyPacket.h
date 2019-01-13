#pragma once
#include <SFML\Network.hpp>
class ThreeIsReadyPacket
{
private:
	bool mIsReady;
	int mPlayerID;
	sf::Packet* mPacket;
public:
	ThreeIsReadyPacket(void);
	ThreeIsReadyPacket(sf::Packet* Packet);
	ThreeIsReadyPacket(bool IsReady, int PlayerID);
	ThreeIsReadyPacket(bool IsReady);
	static int getPacketID(){return 3;}

	bool getReadyState(){return mIsReady;}
	int getPlayerID(){return mPlayerID;}
	sf::Packet* getPacket(){return mPacket;}
};

