#pragma once
#include <SFML\Graphics.hpp>
#include "ServerManager.h"
#include "ClientManager.h"
#include "FivePlayerPacket.h"
#include "Map.h"
class Player
{
	private:

		sf::Clock mClock;
		sf::Time mTimeBetweenSendPacket;
		sf::Vector2f mCameraPosition;
		sf::View mCameraView;
		sf::Vector2f mPosition;
		sf::Vector2f mServerPosition;
		sf::Vector2f mVelocity;

		std::vector<sf::Vector2f> mPoints;

		int mPlayerID;
		sf::CircleShape mCircle;
		//the shared update between the serever and the client
		void SharedUpdate(float DeltaT,Map* Map);
	public:
		Player(void);
		Player(int PlayerID);
		~Player(void);
		//returns the client ID associated with this player
		int getClientID(){return mPlayerID;}
		sf::View getView(){return mCameraView;}
		//send the players state to the clients from the server
		void SendToClients(ServerManager* ServerManager);
		//synce the data from the server
		void SyncFromServer(FivePlayerPacket Packet);
		//draw the player
		void Draw(sf::RenderWindow* Window);
		//updte the player from the client
		void Update(float DeltaT,Map* Map);
		//update for the server for the player
		void Update(float DeltaT,ServerManager* ServerManager,Map* Map);
		void Camera(sf::RenderWindow* Window);
		int EndPointIntersection(Map* Map);
};

