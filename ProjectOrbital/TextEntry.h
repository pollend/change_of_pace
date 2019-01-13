#pragma once
#include <SFML\Graphics.hpp>
class TextEntry
{
	public:
		TextEntry(void);
		TextEntry(float X, float Y, float Width);
		~TextEntry(void);
		void Event(sf::Event Events);
		void Draw(sf::RenderWindow* Window);
		void Clear();
		std::string getString(){return mOutput;}
	private:
		sf::RectangleShape mEntryBox;
		sf::Text mText;
		std::string mOutput;
		float mWidth;
		
};

