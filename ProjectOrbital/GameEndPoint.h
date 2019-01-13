#pragma once
#include <SFML\Graphics.hpp>
class GameEndPoint
{
private:
	sf::Vector2f mPosition;
	sf::Clock mTime;
	sf::RectangleShape mBottomRectangle;
	sf::RectangleShape mMiddleRectangle;
	sf::RectangleShape mTopRectangle;

public:
	GameEndPoint(void);
	GameEndPoint(sf::Vector2f Position);
	~GameEndPoint(void);
	bool EndPointIntersection(sf::Vector2f Position);
	void Update(float DeltaT);
	void Draw(sf::RenderWindow* Window);
};

