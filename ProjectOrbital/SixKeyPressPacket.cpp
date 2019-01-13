#include "SixKeyPressPacket.h"

std::map<sf::Keyboard::Key, bool> SixKeyPressPacket::mKeyPresses = std::map<sf::Keyboard::Key,bool>();

 void SixKeyPressPacket::addKeyToKeyPressPacket(sf::Keyboard::Key Key)
{
	SixKeyPressPacket::mKeyPresses.insert(std::make_pair(Key,false));
}
SixKeyPressPacket::SixKeyPressPacket(sf::Keyboard::Key Key, bool IsPressed)
{
	if(SixKeyPressPacket::mKeyPresses[Key] != IsPressed)
	{
			mPacket = new sf::Packet();
		(*mPacket) << sf::Int32(getPacketID());
		(*mPacket) << sf::Int32(Key);
		(*mPacket) << IsPressed;
		SixKeyPressPacket::mKeyPresses[Key]= IsPressed;
	
	}
	else
	{
		mPacket = NULL;
	}
}

SixKeyPressPacket::SixKeyPressPacket(sf::Packet* Packet)
{
	sf::Int32 KeyID;
	bool lPressed;
	(*Packet) >> KeyID;
	(*Packet) >> mIsPressed;
	mKey= (sf::Keyboard::Key)KeyID;

	delete(Packet);
}

SixKeyPressPacket::~SixKeyPressPacket(void)
{
}