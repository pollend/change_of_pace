#pragma once
#include <iostream>
#include <sstream>
#include <SFML\Graphics.hpp>

class Client
{
	private:
		int mClientID;
		bool mIsReady;
		std::string mPlayerName;		
	public:
		Client(void);
		Client(int ClientID);
		~Client(void);

		//returns the client ID
		int GetClientID(){return mClientID;}
		//get the is Ready State
		bool getReadyState(){return mIsReady;}
		//set the Ready State
		void setIsReadyState(bool IsReady){mIsReady = IsReady;}
		std::string getName(){return mPlayerName;}
};

