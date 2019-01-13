#include "TextEntry.h"

TextEntry::TextEntry()
{
}
TextEntry::TextEntry(float X, float Y, float Width)
{
	mEntryBox.setPosition(X,Y);
	mEntryBox.setSize(sf::Vector2f(Width,20));
	mEntryBox.setOutlineThickness(1);
	mEntryBox.setFillColor(sf::Color::Transparent);
	mText.setFont(sf::Font::getDefaultFont());
	mText.setOrigin(0,0);
	mText.setPosition(X,Y);
	mText.setCharacterSize(20);
	mWidth = Width;
}


TextEntry::~TextEntry(void)
{
}


void TextEntry::Draw(sf::RenderWindow* Window)
{

	Window->draw(mEntryBox);
	Window->draw(mText);
}
void TextEntry::Clear()
{
	//clear the string and update the output
	mOutput = "";
	mText.setString(mOutput);
}

void TextEntry::Event(sf::Event Event)
{
	if(sf::Event::TextEntered == Event.type)
	{
		char lKey = Event.key.code;
		switch(lKey)
		{
			case 8:
				if(mOutput.size() != 0)
					mOutput.pop_back();
			break;
			default:
				mOutput += lKey;
			break;
		}

		mText.setString(mOutput);
	}

}