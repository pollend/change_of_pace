#include "Map.h"
#include "FourTilePacket.h"

Map::Map(void)
{
	mGameStartArea = new GameStartArea(sf::Vector2f(200,720));
}


Map::~Map(void)
{
	delete mGameEndPoint;
	delete mGameStartArea;
}
void Map::Update(float DeltaT,sf::Clock* GameTime)
{
	mGameEndPoint->Update(DeltaT);
	mGameStartArea->Update(GameTime);
}

bool Map::SyncWithServer(ClientManager* ClientManager)
{
	sf::Packet* lMapPacket = ClientManager->GetPacket(FourTilePacket::getPacketID());
	if(!(lMapPacket == NULL))
	{
		FourTilePacket lTileSync(lMapPacket);
		mSquares = lTileSync.getTile();
		mGameEndPoint =new GameEndPoint(lTileSync.getEndPoint());
		return true;
	}
	return false;

}

Tile::TypeOfTile Map::PlayerIntersectTypeTile(sf::Vector2f Point)
{
	for(int x = 0; x <mSquares.size(); x++)
	{
		if(mSquares[x].PointIntersects(Point))
		{
			return mSquares[x].getTile();
		}
	}
	return Tile::SLOWEST;
}


void Map::Generate(float LenghtOfMap,ServerManager* ServerManager)
{
	std::srand((unsigned int)time(NULL));	
	for(int x = 0; x < 100; x++)
	{
		mSquares.push_back(Tile(sf::Vector2f(((float)(std::rand()%100)/(float)100) * LenghtOfMap,((float)(std::rand()%100)/(float)100) *800)));
	}

	//creates an endpoint
	if(ServerManager != NULL)
	{
		mGameEndPoint =new GameEndPoint(sf::Vector2f(LenghtOfMap-50,720/2));
		ServerManager->SendToAllClients(FourTilePacket(mSquares,sf::Vector2f(LenghtOfMap-50,720/2)).getPacket());	
	}
	else
	{
		mGameEndPoint =new GameEndPoint(sf::Vector2f(LenghtOfMap-50,720/2));
	}
}
void Map::Draw(sf::RenderWindow* RenderWindow)
{
	for(int x = mSquares.size()-1; x >= 0; x--)
	{

		mSquares[x].Draw(RenderWindow);
	}
	mGameEndPoint->Draw(RenderWindow);
	mGameStartArea->Draw(RenderWindow);
}