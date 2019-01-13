#include "Tile.h"

Tile::Tile()
{
}
Tile::Tile(sf::Vector2f Position)
{

	int lValue =std::rand()%100;
	 if(lValue < 40)
	 {
		 mType = TypeOfTile::FAST;
		  mRectangle.setFillColor(sf::Color::Color(246,251,150));
	 }
	else if(lValue <80)
	{
		mType = TypeOfTile::MEDIUM;
		mRectangle.setFillColor(sf::Color::Color(155,158,104));
	 }
	else if(lValue <100)
	{
		mType = TypeOfTile::SLOW;
		mRectangle.setFillColor(sf::Color::Color(42,43,31));
	}

	mRectangle.setPosition(Position);
	float lSize = (float)(std::rand()%500)+100;
	mRectangle.setSize(sf::Vector2f(lSize,lSize));
	mRectangle.setOrigin(lSize/2.0f,lSize/2.0f);

	mDiagonal = std::sqrt(lSize * lSize +  lSize * lSize);

	mRectangle.setRotation(std::rand()%360);
}
Tile::Tile(sf::Vector2f Position, float size,TypeOfTile TypeOfTile, float rotation)
{
	 if(TypeOfTile == TypeOfTile::FAST)
	 {
		 mRectangle.setFillColor(sf::Color::Color(246,251,150));
		 mType = TypeOfTile::FAST;
	 }
	else if(TypeOfTile == TypeOfTile::MEDIUM)
	{
		mRectangle.setFillColor(sf::Color::Color(155,158,104));
		mType = TypeOfTile::MEDIUM;
	 }
	else if(TypeOfTile == TypeOfTile::SLOW)
	{
		mRectangle.setFillColor(sf::Color::Color(42,43,31));
		mType = TypeOfTile::SLOW;
	}

	mRectangle.setPosition(Position);
	mRectangle.setSize(sf::Vector2f(size,size));
	mRectangle.setOrigin(size/2,size/2);

	mRectangle.setRotation(rotation);
}


Tile::~Tile(void)
{
}

void Tile::Update()
{
}

bool Tile::PointIntersects(sf::Vector2f Point)
{
	if(mRectangle.getGlobalBounds().contains(Point))
	{
		sf::Rect<float> lDefaultRectangle(sf::Vector2f(mRectangle.getPosition().x -(mRectangle.getSize().x/2.0f),mRectangle.getPosition().y-(mRectangle.getSize().y/2.0f)),mRectangle.getSize());
		sf::Vector2f lDiffrence = sf::Vector2f(Point.x-mRectangle.getPosition().x ,Point.y-mRectangle.getPosition().y);
		float lDistance = std::sqrt(lDiffrence.x * lDiffrence.x + lDiffrence.y * lDiffrence.y);
		float lRotate = std::atan2(lDiffrence.y,lDiffrence.x);

		Point.x = (std::cos(lRotate-(mRectangle.getRotation()*(3.14f/180))) *lDistance)+mRectangle.getPosition().x;
		Point.y = (std::sin(lRotate-(mRectangle.getRotation()*(3.14f/180))) *lDistance)+mRectangle.getPosition().y;

		if(lDefaultRectangle.contains(Point))
		{
			return true;
		}
	}

	return false;
}

void Tile::Draw(sf::RenderWindow* Window)
{
	if(sf::Rect<float>(Window->getView().getCenter().x-(1280/2),Window->getView().getCenter().y,1280,720).intersects(mRectangle.getGlobalBounds()))
	Window->draw(mRectangle);
}