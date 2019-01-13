#pragma once
#include <SFML\Network.hpp>
#include "Tile.h"
class FourTilePacket
{
private:
	std::vector<Tile> mTile;
	sf::Packet* mPacket;
	sf::Vector2f mEndPoint;
public:
	FourTilePacket(void);
	FourTilePacket(std::vector<Tile> Tile,sf::Vector2f Endpoint);
	FourTilePacket(sf::Packet* Packet);

	~FourTilePacket(void);

	static int getPacketID(){return 4;}
	sf::Packet* getPacket(){return mPacket;}
	std::vector<Tile> getTile(){return mTile;}
	sf::Vector2f getEndPoint(){return mEndPoint;}

};

