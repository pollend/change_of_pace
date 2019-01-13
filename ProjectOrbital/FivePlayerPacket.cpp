#include "FivePlayerPacket.h"


FivePlayerPacket::FivePlayerPacket(void)
{
}

FivePlayerPacket::FivePlayerPacket(int ClientID,sf::Vector2f Position,sf::Vector2f Velocity)
{
	mPacket = new sf::Packet();

	(*mPacket) << getPacketID();
	(*mPacket) << ClientID;
	(*mPacket) << Position.x;
	(*mPacket) << Position.y;
	(*mPacket) << Velocity.x;
	(*mPacket) << Velocity.y;
}
FivePlayerPacket::FivePlayerPacket(sf::Packet* Packet)
{
	(*Packet)>>mClientID;
	(*Packet) >> mPosition.x;
	(*Packet) >> mPosition.y;
	(*Packet) >> mVelocity.x;
	(*Packet) >> mVelocity.y;
	delete(Packet);
}


FivePlayerPacket::~FivePlayerPacket(void)
{
}
