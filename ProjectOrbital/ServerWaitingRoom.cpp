#include "ServerWaitingRoom.h"
#include "TwoMessagePacket.h"
#include "ThreeIsReadyPacket.h"
#include "OneClientPacket.h"

ServerWaitingRoom::~ServerWaitingRoom(void)
{
}

ServerWaitingRoom::ServerWaitingRoom(ServerManager* ServerManager, std::vector<Client*>* Players, short Port)
{
	mNextID = 0;
	mPlayers = Players;
	mServerManager = ServerManager;

	//set up client Listner
	mClientListner = new sf::TcpListener();
	mClientListner->listen(Port);

	mListnerThread = new sf::Thread(&ServerWaitingRoom::ListenForClients,this);
	mListnerThread->launch();

}

void ServerWaitingRoom::StartListnerThread()
{	
	mListnerThread->launch();
}
void ServerWaitingRoom::StopListnerThread()
{
	mListnerThread->terminate();
}

void ServerWaitingRoom::ListenForClients()
{
	mClientListner->setBlocking(true);
	while(true)
	{
		
		sf::TcpSocket* client = new sf::TcpSocket();
		if (mClientListner->accept((*client)) == sf::Socket::Done)
		 {
			 // A new client just connected!
			 std::cout << "New connection received from " << client->getRemoteAddress() << std::endl;
			 Client* lNewClient = new Client(mNextID);
			 //send the ID
			 sf::Packet lRegistartionID ;
			 lRegistartionID<< sf::Int32(mNextID);
			 client->send(lRegistartionID);

			 //add the client and push it to the client list
			 mServerManager->AddClient(lNewClient,client);

			 //lock it up so the main thread dosent interfere
			 mMainLock.lock();
			 //send client Syncing packet
			 for(int x = 0; x <mPlayers->size(); x++)
			 {
				 mServerManager->SendToClient(OneClientPacket((*mPlayers)[x]).getPacket(),lNewClient);
			 }

			 //send to every one notifiying the player ID
			 mPlayers->push_back(lNewClient);
			 mServerManager->SendToAllClients(OneClientPacket(lNewClient).getPacket());
			 mNextID++;
			 mMainLock.unlock();
			 
		 }
	}

}

void ServerWaitingRoom::Update()
{
	mMainLock.lock();
	for(int x=0 ; x < mPlayers->size(); x++)
	{
		sf::Packet* lPacket = mServerManager->GetPackets((*mPlayers)[x],3);
		if(lPacket != NULL)
		{
			ThreeIsReadyPacket lReadyPacket = ThreeIsReadyPacket( );
			(*mPlayers)[x]->setIsReadyState(lReadyPacket.getReadyState());
			mServerManager->SendToAllClients(ThreeIsReadyPacket(lReadyPacket.getReadyState(),(*mPlayers)[x]->GetClientID()).getPacket());
		}
	}

	//send packets to all the clients
	for(int x=0 ; x < mPlayers->size(); x++)
	{
		
		sf::Packet* lPacket = mServerManager->GetPackets((*mPlayers)[x],2);
		if(lPacket != NULL)
		{
			std::string lMessage = TwoMessagePacket(lPacket).getMessage();
			std::cout << lMessage << "\n";
			mServerManager->SendToAllClients(TwoMessagePacket(lMessage).getPacket());
		}
	}
	mMainLock.unlock();

}

bool ServerWaitingRoom::IsPlayersAllReady()
{
	bool lReady = true;
	if(mPlayers->size() > 0)
	{
		for(int x = 0; x < mPlayers->size(); x++)
		{
			if((*mPlayers)[x]->getReadyState() == false)
			{
				lReady = false;
				break;
			}
		}
	}
	else
	{
		return false;
	}
	return lReady;
}