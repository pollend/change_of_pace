#include "ServerManager.h"
#include <SFML\Network.hpp>

#define NUMBER_PACKETS 180

ServerManager::ServerManager(void)
{
	mSockets = std::map<int,ServerSocket*>();
}


ServerManager::~ServerManager(void)
{
}


void ServerManager::AddClient(Client* Client,sf::TcpSocket* Socket)
{

	mSocketLock.lock();
	mSockets.insert(std::make_pair(Client->GetClientID(),new ServerSocket(Socket)));
	mSocketLock.unlock();
}

void ServerManager::SendToAllClients(sf::Packet* Packet)
{
	mSocketLock.lock();
	//send the packet to all the clients
	for( std::map<int,ServerSocket*>::iterator iterator = mSockets.begin(); iterator != mSockets.end(); iterator++) {
		iterator->second->SendPacket(Packet);
	}
	delete(Packet);
	mSocketLock.unlock();
}
//Send to the selected Packets
void ServerManager::SendToClient(sf::Packet* Packet,Client* client)
{
	mSocketLock.lock();
	mSockets[client->GetClientID()]->SendPacket(Packet);
	delete(Packet);
	mSocketLock.unlock();
}

void ServerManager::SendToAllClientsExcept(sf::Packet* Packet,Client* client)
{
		mSocketLock.lock();
	//send the packet to all the clients
	for( std::map<int,ServerSocket*>::iterator iterator = mSockets.begin(); iterator != mSockets.end(); iterator++) {
		//send to everyone else except the client
		if(iterator->first != (client->GetClientID()-1))
		{
			iterator->second->SendPacket(Packet);
		}
	}
	delete(Packet);
	mSocketLock.unlock();
}
//returns a packet by the client
//
//returns null if their isn't any packets avaliable to get
sf::Packet* ServerManager::GetPackets(Client* client,int ID)
{
	mSocketLock.lock();
	sf::Packet* lPacket = mSockets[client->GetClientID()]->GetPacket(ID);
		mSocketLock.unlock();
	return lPacket;
}


sf::Packet* ServerManager::GetPackets(int client,int ID)
{
	mSocketLock.lock();
	sf::Packet* lPacket = mSockets[client]->GetPacket(ID);
		mSocketLock.unlock();
	return lPacket;
}

