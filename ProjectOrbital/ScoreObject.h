#pragma once
#include <iostream>
#include <SFML\Network.hpp>
class ScoreObject
{
	private:
		float mTime;
		std::string mName;
		//Client* mClient;
	public:
		ScoreObject(void);
		ScoreObject(float Time, std::string Name);
		//ScoreObject(float Time, std::string Name,Client* Client);
		~ScoreObject(void);

		float getTime(){return mTime;}
		std::string getName(){return mName;}
};

