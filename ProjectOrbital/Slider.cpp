#include "Slider.h"


Slider::Slider(float X, float Y, float Width)
{
	mInnerRectangle.setPosition(X,Y);
	mInnerRectangle.setSize(sf::Vector2f(Width,10));
	mInnerRectangle.setOrigin(0,5);

	mSlideBar.setOrigin(sf::Vector2f(5,10));
	mSlideBar.setPosition(X,Y);
	mSlideBar.setSize(sf::Vector2f(10,20));

	mLeft = X;
	mRight = X + Width;


}

float Slider::getPercent()
{
	return (mSlideBar.getPosition().x-mLeft)/(mRight-mLeft);
}
void Slider::Update(sf::RenderWindow* Window)
{
	//mouse is in the box
	if(mSlideBar.getGlobalBounds().contains(Window->convertCoords(sf::Mouse::getPosition((*Window)))))
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mSlideBar.setPosition(sf::Mouse::getPosition((*Window)).x,mSlideBar.getPosition().y);
			if(mSlideBar.getPosition().x >mRight)
			{
				mSlideBar.setPosition(mRight,mSlideBar.getPosition().y);
			}
			else if(mSlideBar.getPosition().x <mLeft)
			{
				mSlideBar.setPosition(mLeft,mSlideBar.getPosition().y);
			}
		}
	}
}

void Slider::Draw(sf::RenderWindow* Window)
{
	Window->draw(mInnerRectangle);
	Window->draw(mSlideBar);
}

Slider::Slider(void)
{
}


Slider::~Slider(void)
{
}
