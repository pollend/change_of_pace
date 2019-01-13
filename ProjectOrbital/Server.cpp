#include "Server.h"
#include <iostream>
#include "OneClientPacket.h"
#include "TwoMessagePacket.h"
#include "ThreeIsReadyPacket.h"
Server::Server(short Port)
{

	mServerManager = new ServerManager();
	mPlayers = new std::vector<Client*>();
	
	mServerWaitingRoom = new ServerWaitingRoom(mServerManager,mPlayers,Port);

	mMainThread = new sf::Thread(&Server::ServerMain,this);
	mMainThread->launch();
	
	mServerState = ServerState::WAITING_ROOM;
}


Server::~Server(void)
{

}

void Server::ServerMain()
{
	while(true)
	{

		switch(mServerState)
		{
			case ServerState::WAITING_ROOM:
				mServerWaitingRoom->Update();
				if(mServerWaitingRoom->IsPlayersAllReady())
				{
					mServerWaitingRoom->StopListnerThread();
					mServerState = ServerState::GAME_SCREEN;
					mServerGameScreen = new ServerGameScreen(mServerManager,mPlayers);
				}
			break;
			case ServerState::GAME_SCREEN:
				//update the GameScreen 
				mServerGameScreen->Update(mServerManager);
			break;
		}
	}
}

void Server::KillServer()
{
	mMainThread->terminate();
	delete(mServerWaitingRoom);
	delete(mServerManager);
	mMainThread->terminate();
	delete(mMainThread);
	for(int x = 0; x < mPlayers->size(); x++)
	{
		delete((*mPlayers)[x]);
	}
	delete(mPlayers);

}

