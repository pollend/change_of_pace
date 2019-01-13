#pragma once
#include <SFML\Graphics.hpp>
#include "ClientManager.h"
#include "ServerManager.h"
#include "GameEndPoint.h"
#include "Tile.h"
#include "GameStartArea.h"
class Map
{
private:
	std::vector<Tile> mSquares;
	GameEndPoint* mGameEndPoint;
	GameStartArea* mGameStartArea;
public:
	bool SyncWithServer(ClientManager* ClientManager);
	void Generate(float LenghtOfMap,ServerManager* ServerManager);
	void Update(float DeltaT,sf::Clock* GameTime);
	void Draw(sf::RenderWindow* RenderWindow);

	GameStartArea* getStartArea(){return mGameStartArea;}
	GameEndPoint* getGameEndPoint(){return mGameEndPoint;}

	Tile::TypeOfTile PlayerIntersectTypeTile(sf::Vector2f Point);
	Map(void);
	~Map(void);
};

