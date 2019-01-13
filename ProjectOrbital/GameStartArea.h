#pragma once
#include <SFML\Graphics.hpp>
class GameStartArea
{
private:
	sf::RectangleShape mRectangle;
	bool mStartAreaActive;
	sf::Text mStartText;
	sf::Font mFont;
public:
	GameStartArea();
	GameStartArea(sf::Vector2f Size);
	sf::Vector2f CollisionOffset(sf::Rect<float> Rectangle);
	bool isColliding(sf::Rect<float> Rectangle);
	~GameStartArea(void);
	void Update(sf::Clock* GameTime);
	void Draw(sf::RenderWindow* Window);
	void DisableStartArea();
};

