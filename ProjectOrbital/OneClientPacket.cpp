#include "OneClientPacket.h"
OneClientPacket::OneClientPacket(sf::Packet* Packet)
{
		sf::Int32 lUserID;
		(*Packet) >> lUserID;
		mClient = new Client(lUserID);	
		delete(Packet);
}
OneClientPacket::OneClientPacket(Client* Client)
{
	mPacket = new sf::Packet();
	(*mPacket) << sf::Int32(getPacketID());
	(*mPacket) << sf::Int32(Client->GetClientID());
	//mPacket= lPacket;

}


OneClientPacket::~OneClientPacket(void)
{
}


