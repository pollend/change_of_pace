#include "FourTilePacket.h"
FourTilePacket::FourTilePacket(void)
{
}
FourTilePacket::FourTilePacket(std::vector<Tile> Tile,sf::Vector2f Endpoint)
{
	mPacket = new sf::Packet();
	(*mPacket) << sf::Int32(getPacketID());

	(*mPacket) << sf::Int32(Tile.size());
	for(int x = 0; x < Tile.size(); x++)
	{

		(*mPacket) << sf::Int32(Tile[x].getTile());
		(*mPacket) << Tile[x].getRectangle().getPosition().x;
		(*mPacket) << Tile[x].getRectangle().getPosition().y;
		(*mPacket) << Tile[x].getRectangle().getSize().x;
		(*mPacket) << Tile[x].getRectangle().getRotation();
	}
	(*mPacket) << Endpoint.x;
	(*mPacket) << Endpoint.y;
}
FourTilePacket::FourTilePacket(sf::Packet* Packet)
{
	sf::Int32 lTileID;
	sf::Int32 lNumberOfTiles;
	(*Packet) >> lNumberOfTiles;
	for(int x = lNumberOfTiles-1; x >= 0; x--)
	{
		float lX;
		float lY;
		float lSize;
		float lRotation;
		(*Packet) >> lTileID >> lX>>lY>>lSize>>lRotation;
		mTile.push_back( Tile(sf::Vector2f(lX,lY),lSize,(Tile::TypeOfTile)lTileID,lRotation));
	}
	(*Packet) >>mEndPoint.x;
	(*Packet) >>mEndPoint.y;

	delete Packet;
}

FourTilePacket::~FourTilePacket(void)
{
}
