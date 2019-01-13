#include "ThreeIsReadyPacket.h"


ThreeIsReadyPacket::ThreeIsReadyPacket(void)
{

}

ThreeIsReadyPacket::ThreeIsReadyPacket(sf::Packet* Packet)
{
	(*Packet)>>mPlayerID;
	(*Packet) >> mIsReady;
	delete(Packet);
}

ThreeIsReadyPacket::ThreeIsReadyPacket(bool IsReady, int PlayerID)
{
	mPacket= new sf::Packet();
	(*mPacket) << sf::Int32(getPacketID());

	(*mPacket) << sf::Int32(PlayerID);
	//(*mPacket) << IsReady;

}

ThreeIsReadyPacket::ThreeIsReadyPacket(bool IsReady)
{
	 mPacket= new sf::Packet();
	(*mPacket) << sf::Int32(getPacketID());

	(*mPacket) << sf::Int32(1);
	(*mPacket) << IsReady;

}