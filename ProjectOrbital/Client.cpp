#include "Client.h"

Client::Client(void)
{
	mIsReady = false;
}

Client::Client(int ClientID)
{
	mClientID = ClientID;
	std::ostringstream lString;
	lString << "player" ;
	lString <<  ClientID;
	mPlayerName = lString.str();
	mIsReady = false;
}



Client::~Client(void)
{
}
