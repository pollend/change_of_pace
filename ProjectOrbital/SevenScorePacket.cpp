#include "SevenScorePacket.h"


SevenScorePacket::SevenScorePacket(void)
{
}

SevenScorePacket::SevenScorePacket(sf::Packet* Packet)
{
	sf::Int32 lSize;
	(*Packet)>>lSize;
	for(int x = 0 ; x < lSize; x++)
	{
		std::string lString;
		float lTime;
		sf::Int32 lNameSize;
		(*Packet) >>lNameSize;
		for(int i = 0; i  < lNameSize; i++)
		{
			sf::Int32 ldata;
			(*Packet) >> ldata;
			lString += ldata;;
		}
		(*Packet) >> lTime;
		mScoreObject.push_back(ScoreObject(lTime,lString));
	}
	delete Packet;
}
SevenScorePacket::SevenScorePacket(std::vector<ScoreObject> ScoreObject)
{
	mPacket = new sf::Packet();
	(*mPacket)<<SevenScorePacket::getPacketID();
	(*mPacket) << ScoreObject.size();
	for(int x = ScoreObject.size()-1; x >= 0;x--)
	{
		(*mPacket) << sf::Int32(ScoreObject[x].getName().length());
		for(int i = 0; i < ScoreObject[x].getName().length();i++)
		{
			(*mPacket) << sf::Int32(ScoreObject[x].getName()[i]);
		}
		(*mPacket) << (ScoreObject[x].getTime());
	}
}


SevenScorePacket::~SevenScorePacket(void)
{
}
