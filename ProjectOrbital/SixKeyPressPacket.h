#pragma once
#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>


class SixKeyPressPacket
{
private:
	sf::Packet* mPacket;
	sf::Keyboard::Key mKey;
	bool mIsPressed;
	static std::map<sf::Keyboard::Key, bool> mKeyPresses;
public:

	static void addKeyToKeyPressPacket(sf::Keyboard::Key Key);

	SixKeyPressPacket(sf::Keyboard::Key Key, bool IsPerssed);
	SixKeyPressPacket(sf::Packet* Packet);
	~SixKeyPressPacket();
	static int getPacketID(){return 6;}

	sf::Keyboard::Key getKey(){return mKey;}
	bool getIsKeyPressed(){return mIsPressed;}

	sf::Packet* getPacket(){return mPacket;}
};
