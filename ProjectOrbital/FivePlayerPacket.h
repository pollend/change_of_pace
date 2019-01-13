#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
class FivePlayerPacket
{
private:
	sf::Vector2f mPosition;
	sf::Vector2f mVelocity;
	sf::Packet* mPacket;
	int mClientID;
public:
	FivePlayerPacket(void);
	FivePlayerPacket(int ClientID,sf::Vector2f Position,sf::Vector2f Velocity);
	FivePlayerPacket(sf::Packet* Packet);

	static int getPacketID(){return 5;}
	sf::Packet* getPacket(){return mPacket;}
	sf::Vector2f getLocation(){return mPosition;}
	sf::Vector2f getVelocity(){return mVelocity;}
	int getClientID(){return mClientID;}
	~FivePlayerPacket(void);
};

