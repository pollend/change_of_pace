#include "TwoMessagePacket.h"


TwoMessagePacket::TwoMessagePacket(sf::Packet* Packet)
{

	sf::Int32 lIndex;
	(*Packet) >> lIndex;
	for(int x = 0; x < lIndex; x++)
	{
		sf::Int32 lChar;
		(*Packet) >> lChar;
		mMessage += lChar;
	}
}
TwoMessagePacket::TwoMessagePacket(std::string String)
{

	mPacket = new sf::Packet();
	(*mPacket) << sf::Int32(getPacketID());
	(*mPacket) << sf::Int32(String.size());
	for(int x = 0; x < String.size(); x++)
	{
		(*mPacket) << sf::Int32(String[x]);
	}
}

TwoMessagePacket::~TwoMessagePacket(void)
{
}
