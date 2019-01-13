#include "Player.h"
#include"SixKeyPressPacket.h"
Player::Player(void)
{

}


Player::~Player(void)
{
}

Player::Player (int PlayerID)
{
	mCameraView.setSize(1280,720);
	mCameraView.setCenter(1280/2,720/2);

	mCircle = sf::CircleShape(5,20);
	mCircle.setOrigin(5.0,5.0);
	mCircle.setFillColor(sf::Color::Red);
	mPlayerID = PlayerID;
}

void Player::SendToClients(ServerManager* ServerManager)
{
	sf::Packet* lPacket = ServerManager->GetPackets(mPlayerID,SixKeyPressPacket::getPacketID());
	if(lPacket != NULL)
	{
		SixKeyPressPacket lKey(lPacket);
		if(lKey.getIsKeyPressed())
		{
			switch( lKey.getKey())
			{
				case sf::Keyboard::W:
					mVelocity.y = -1;
					break;
				case sf::Keyboard::A:
					mVelocity.x = -1;
					break;
				case sf::Keyboard::S:
					mVelocity.y = 1;
					break;
				case sf::Keyboard::D:
					mVelocity.x =1;
					break;
			}
		}
		else
		{
			switch( lKey.getKey())
			{
				case sf::Keyboard::W:
					mVelocity.y = 0;
					break;
				case sf::Keyboard::A:
					mVelocity.x = 0;
					break;
				case sf::Keyboard::S:
					mVelocity.y = 0;
					break;
				case sf::Keyboard::D:
					mVelocity.x =0;
					break;
			}
		}
	}

}
void Player::SyncFromServer(FivePlayerPacket Packet)
{
	if(Packet.getClientID() == mPlayerID)
	{
		mServerPosition = Packet.getLocation();
		mVelocity = Packet.getVelocity();
	}
}

void Player::Update(float DeltaT,Map* Map)
{
	SharedUpdate(DeltaT,Map);
	
	sf::Vector2f lDiffrence = sf::Vector2f(mServerPosition.x-mPosition.x,mServerPosition.y-mPosition.y);
	mPosition.x += (lDiffrence.x*.5f) * DeltaT;
	mPosition.y += (lDiffrence.y*.5f) * DeltaT;
	if(mPoints.size() != 0)
	{
		if(mPosition.x != mPoints[mPoints.size()-1].x &&mPosition.y != mPoints[mPoints.size()-1].y)
		mPoints.push_back(mPosition);
		for(int x = 0; x < mPoints.size(); x++)
		{
			if(mPoints[x].x < mCameraView.getCenter().x -640-640)
			{
				mPoints.erase(mPoints.begin() + x);
			}
		}
	}
	else
	{
		mPoints.push_back(mPosition);
	}

	//check the change in x and move the camera accordingly
	float lChangeX =  (DeltaT * -((mCameraView.getCenter().x-mPosition.x) * .5f));
	if(mCameraView.getCenter().x -640+lChangeX > 0)
	{
		mCameraView.move(sf::Vector2f( lChangeX,0));
	}

}
void Player::Update(float DeltaT,ServerManager* ServerManager,Map* Map)
{
	SharedUpdate(DeltaT,Map);
	sf::Time lTime = mClock.getElapsedTime() -mTimeBetweenSendPacket;
	if(lTime.asMilliseconds() >50)
	{
		ServerManager->SendToAllClients(FivePlayerPacket(mPlayerID,mPosition,mVelocity).getPacket());
		mTimeBetweenSendPacket = mClock.getElapsedTime() ;
	}
}
void Player::SharedUpdate(float DeltaT,Map* Map)
{

	float lNormal =std::sqrt(mVelocity.x * mVelocity.x + mVelocity.y *mVelocity.y);
	if(lNormal != 0)
	{
		Tile::TypeOfTile mType = Map->PlayerIntersectTypeTile(mPosition);
		sf::Vector2f lNormalize = sf::Vector2f(mVelocity.x/lNormal,mVelocity.y/lNormal);

		//in the start area speed is 100
		if(Map->getStartArea()->isColliding(sf::Rect<float>(mPosition.x, mPosition.y,10,10)) )
		{
			mPosition.x += lNormalize.x * DeltaT*200;
			mPosition.y += lNormalize.y* DeltaT*200;
			mPosition += Map->getStartArea()->CollisionOffset(sf::Rect<float>(mPosition.x -5.0f,mPosition.y -5.0f,5*2,5*2));
		}
		else
		{
			if(mType == Tile::SLOWEST)
			{
				mPosition.x += lNormalize.x * DeltaT*25;
				mPosition.y += lNormalize.y* DeltaT*25;
			}
			else if(mType == Tile::SLOW)
			{
				mPosition.x += lNormalize.x * DeltaT*50;
				mPosition.y += lNormalize.y* DeltaT*50;
			}
			else if(mType == Tile::MEDIUM)
			{
				mPosition.x += lNormalize.x * DeltaT*100;
				mPosition.y += lNormalize.y* DeltaT*100;
			}
			else if(mType == Tile::FAST)
			{
				mPosition.x += lNormalize.x * DeltaT*200;
				mPosition.y += lNormalize.y* DeltaT*200;
			}
		}
	}
}

int Player::EndPointIntersection(Map* Map)
{
	if(Map->getGameEndPoint()->EndPointIntersection(mPosition))
	{
		return mPlayerID;
	}
	return -1;
}

void Player::Draw(sf::RenderWindow* Window)
{
	sf::VertexArray lLines(sf::LinesStrip,mPoints.size());
	for(int x = 0; x < mPoints.size(); x++)
	{
		lLines[x].position = mPoints[x];
	}

	mCircle.setPosition(mPosition.x,mPosition.y);
	Window->draw(mCircle);
	Window->draw(lLines);
}

void Player::Camera(sf::RenderWindow* Window)
{
	Window->setView(mCameraView);
}

