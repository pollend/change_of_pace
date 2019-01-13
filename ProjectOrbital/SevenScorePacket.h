#pragma once
#include <SFML\Network.hpp>
#include "ScoreObject.h"
class SevenScorePacket
{
private:
	std::vector<ScoreObject> mScoreObject;
	sf::Packet* mPacket;
public:
	SevenScorePacket(void);
	SevenScorePacket(sf::Packet* Packet);
	SevenScorePacket(std::vector<ScoreObject> ScoreObject);
	~SevenScorePacket(void);

	static int getPacketID(){return 7;}
	sf::Packet* getPacket(){return mPacket;}
	std::vector<ScoreObject> getScoreObjects(){return mScoreObject;}
};

