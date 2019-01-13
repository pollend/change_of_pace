#include "ServerGameScreen.h"
#include "SevenScorePacket.h"

ServerGameScreen::ServerGameScreen(ServerManager* ServerManager,std::vector<Client*>* Players)
{
	mGameTime = new sf::Clock;
	mMap = new Map();
	mMap->Generate(500,ServerManager);
	mClients =Players;
	for(int x = 0; x < mClients->size(); x++)
	{
		mPlayers.push_back(Player((*mClients)[x]->GetClientID()));
	}

	mElapsedTime =  mFrameRate.getElapsedTime();
}


ServerGameScreen::~ServerGameScreen(void)
{

}

void ServerGameScreen::Update(ServerManager* ServerManager)
{	
	float lDeltaTime = mFrameRate.getElapsedTime().asSeconds()- mElapsedTime.asSeconds() ;
	mElapsedTime = mFrameRate.getElapsedTime();

	for(int x = 0; x < mPlayers.size(); x++)
	{
		mPlayers[x].SendToClients(ServerManager);
		mPlayers[x].Update(lDeltaTime,ServerManager,mMap);
		int lPlayerID =mPlayers[x].EndPointIntersection(mMap);
		if(lPlayerID != -1)
		{
			for(int x = 0; x < mClients->size(); x++)
			{
				if(lPlayerID == (*mClients)[x]->GetClientID())
				{
					mScore.push_back((*mClients)[x]);
					mScoreObject.push_back(ScoreObject(mGameTime->getElapsedTime().asSeconds(),(*mClients)[x]->getName()));
				}
			}
			for(int i = 0;i < mScore.size(); i++)
			{
				SevenScorePacket lScorePacket = SevenScorePacket(mScoreObject);
				ServerManager->SendToClient(lScorePacket.getPacket(),mScore[x]);
			}
			
			mPlayers.erase(mPlayers.begin() +x);
			break;
		}
	}
	mMap->Update(lDeltaTime,mGameTime);

}
