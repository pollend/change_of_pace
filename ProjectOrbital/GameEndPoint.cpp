#include "GameEndPoint.h"
#define NUMBER_PARTICLES 30

GameEndPoint::GameEndPoint(void)
{
}

GameEndPoint::GameEndPoint(sf::Vector2f Position)
{
	mPosition =Position;
	mBottomRectangle.setPosition(Position);
	mMiddleRectangle.setPosition(Position);
	mTopRectangle.setPosition(Position);

	mBottomRectangle.setSize(sf::Vector2f(50,50));
	mBottomRectangle.setOrigin(25,25);
	mBottomRectangle.setFillColor(sf::Color::White);

	mMiddleRectangle.setSize(sf::Vector2f(50,50));
	mMiddleRectangle.setOrigin(25,25);
	mMiddleRectangle.setFillColor(sf::Color::Color(75,73,71));

	mTopRectangle.setSize(sf::Vector2f(45,45));
	mTopRectangle.setOrigin(45/2.0,45/2.0);
	mTopRectangle.setFillColor(sf::Color::Color(135,135,135));
	
}

GameEndPoint::~GameEndPoint(void)
{
}

bool GameEndPoint::EndPointIntersection(sf::Vector2f Position)
{
	if(mBottomRectangle.getGlobalBounds().contains(Position))
	{
		return true;
	}
	return false;
}

void GameEndPoint::Update(float DeltaT)
{
	mBottomRectangle.setRotation(mTime.getElapsedTime().asSeconds()*200);
	mMiddleRectangle.setRotation(-mTime.getElapsedTime().asSeconds()*200);
	mTopRectangle.setRotation(mTime.getElapsedTime().asSeconds()*300);

	mTopRectangle.setScale(std::sin(mTime.getElapsedTime().asSeconds())*1,std::sin(mTime.getElapsedTime().asSeconds())*1);


}

void GameEndPoint::Draw(sf::RenderWindow* Window)
{
	Window->draw(mBottomRectangle);
	Window->draw(mMiddleRectangle);
	Window->draw(mTopRectangle);
}