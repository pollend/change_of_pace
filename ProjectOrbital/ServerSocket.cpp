#include "ServerSocket.h"
#define NUMBER_PACKETS 128

ServerSocket::ServerSocket(void)
{
}

ServerSocket::ServerSocket(sf::TcpSocket* Socket)
{
	//declare the packet array with the number of Packets
	mPackets = new std::list<sf::Packet*>[NUMBER_PACKETS];

	mClientSocket = Socket;
	mSocketListner = new sf::Thread(&ServerSocket::SocketListner,this);
	//launch the socket
	mSocketListner->launch();
}

ServerSocket::~ServerSocket(void)
{
	//terminate the listener and delete it
	mSocketListner->terminate();
	delete(mSocketListner);
	//delete the socket
	delete(mSocketListner);
}
//get the packets and return null if non exist
sf::Packet* ServerSocket::GetPacket(int ID)
{
	
	//lock the vector
	mPacketLock.lock();
	sf::Packet* lPacket = NULL;
	if(mPackets[ID-1].size() != 0)
	{
		 lPacket = mPackets[ID-1].front();
		mPackets[ID-1].pop_front();
	}
	mPacketLock.unlock();
	return lPacket;
	
}
//Send a packet back to the server
void ServerSocket::SendPacket(sf::Packet* Packet)
{
	mClientSocket->send(*Packet);
}

//listin to the sockListner
void ServerSocket::SocketListner()
{
	mClientSocket->setBlocking(true);
	while(true)
	{
		sf::Packet* mPacket = new sf::Packet();
		mClientSocket->receive(*mPacket);
		sf::Int32 lPacketID;
		*mPacket >> lPacketID;
		mPacketLock.lock();
		mPackets[lPacketID-1].push_back(mPacket);
		mPacketLock.unlock();
	}
}