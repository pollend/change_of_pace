#pragma once
#include <SFML\Graphics.hpp>
class Tile
{
public:
	enum TypeOfTile{
		SLOWEST,SLOW,MEDIUM,FAST
	};
	private:
		sf::Vector2f mPoint;
		sf::RectangleShape mRectangle;
		TypeOfTile mType;
		float mDiagonal;
	public:
		sf::RectangleShape getRectangle(){return mRectangle;}
		TypeOfTile getTile(){return mType;}
	

		Tile();
		Tile(sf::Vector2f Position);
		Tile(sf::Vector2f Position, float size,TypeOfTile TypeOfTile, float rotation);
		~Tile(void);
		bool PointIntersects(sf::Vector2f Point);

	void Update();
	void Draw(sf::RenderWindow* Window);
};

