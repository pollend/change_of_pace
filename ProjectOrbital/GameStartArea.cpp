#include "GameStartArea.h"
#include <sstream>
GameStartArea::GameStartArea(){}
GameStartArea::GameStartArea(sf::Vector2f Size)
{
	mRectangle.setSize(Size);
	mRectangle.setFillColor(sf::Color(255,168,0));
	mStartAreaActive = true;
	mStartText = sf::Text();
	mStartText.setCharacterSize(50);
	mStartText.setPosition(20,(720/2)-(50/2));
	mStartText.setString("01234566789");
	if(mFont.loadFromFile("Assets//press.ttf"))
	mStartText.setFont(mFont);
	
}


GameStartArea::~GameStartArea(void)
{
}

sf::Vector2f GameStartArea::CollisionOffset(sf::Rect<float> Rectangle)
{
	if(Rectangle.left + Rectangle.width > mRectangle.getPosition().x + mRectangle.getSize().x)
	{
		return sf::Vector2f((mRectangle.getPosition().x + mRectangle.getSize().x)-(Rectangle.left + Rectangle.width ),0);
	}
	else if(Rectangle.left  < mRectangle.getPosition().x )
	{
		return sf::Vector2f(-Rectangle.left + mRectangle.getPosition().x,0);
	}
	else if(Rectangle.top + Rectangle.height > mRectangle.getPosition().y + mRectangle.getSize().y)
	{
		return sf::Vector2f(0,(mRectangle.getPosition().y+ mRectangle.getSize().y)-(Rectangle.top + Rectangle.height ));
	}
	else if(Rectangle.top  < mRectangle.getPosition().y )
	{
		return sf::Vector2f(0,mRectangle.getPosition().y-Rectangle.top);
	}
	return sf::Vector2f(0,0);
}

bool GameStartArea::isColliding(sf::Rect<float> Rectangle)
{
	if(mStartAreaActive)
	{
			return mRectangle.getGlobalBounds().intersects(Rectangle);
	}
	return false;
}

void GameStartArea::Update(sf::Clock* GameTime)
{
	if( GameTime->getElapsedTime().asSeconds() > 10)
	{
		DisableStartArea();
	}

	std::stringstream lOStringStream;
	lOStringStream <<((int)(std::abs(GameTime->getElapsedTime().asSeconds()-11)));
	std::string lString = lOStringStream.str();
	mStartText.setString(lString);
}

void GameStartArea::Draw(sf::RenderWindow* Window)
{
	if(mStartAreaActive)
	{
		Window->draw(mRectangle);
		Window->draw(mStartText);
	}
}
void GameStartArea::DisableStartArea()
{
	mStartAreaActive = false;
}