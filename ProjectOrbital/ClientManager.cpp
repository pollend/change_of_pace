#include "ClientManager.h"
#include <iostream>
#define NUMBER_PACKETS 180
ClientManager::ClientManager()
{
}

ClientManager::ClientManager(std::string IPAdress,unsigned short port)
{
	mPackets = new std::list<sf::Packet*>[NUMBER_PACKETS];

	mSocket.connect(IPAdress,port);
	mSocket.setBlocking(true);

	//get the ID
	sf::Packet lRegistrationPacket;
	mSocket.receive(lRegistrationPacket);
	sf::Int32 lID;
	lRegistrationPacket >> lID;
	mClientID = lID;

	//start the socket listner
	mSocketListner = new sf::Thread(&ClientManager::SocketListner,this);
	mSocketListner->launch();
}

void ClientManager::SocketListner()
{

	mSocket.setBlocking(true);
	while(true)
	{
		sf::Packet* lPacket = new sf::Packet();
		mSocket.receive(*lPacket);
		sf::Int32 lID;
		(*lPacket) >> lID;

		mPacketLock.lock();
		mPackets[lID-1].push_back(lPacket);
		mPacketLock.unlock();
	}
}

sf::Packet* ClientManager::GetPacket(int PacketID)
{	
	//lock the vector
	mPacketLock.lock();
	sf::Packet* lPacket = NULL;
	if(mPackets[PacketID-1].size() != 0)
	{
		 lPacket = mPackets[PacketID-1].front();
		mPackets[PacketID-1].pop_front();
	}
	mPacketLock.unlock();
	return lPacket;
}


ClientManager::~ClientManager(void)
{
	for(int x = 0; x <NUMBER_PACKETS;x++)
	{
		for(int y = 0; y < mPackets[x].size();y++)
		{
			//getting rid of left over packet
			//deletes the packt and pop if off
			sf::Packet* lPacket = mPackets[x].front();
			delete(lPacket);
			mPackets[x].pop_front();
		}
	}
	//delete all the packets
	delete [] mPackets;
	delete(mSocketListner);
}

void ClientManager::SendToServer(sf::Packet* Packet)
{
	if(Packet != NULL)
	{
		mSocket.send((*Packet));
		delete(Packet);
	}
}