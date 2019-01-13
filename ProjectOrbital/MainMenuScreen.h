#pragma once
#include "IScreen.h"
#include "TextEntry.h"
 class MainMenuScreen : public IScreen
{
public:
	MainMenuScreen(void);
	~MainMenuScreen(void);

	virtual void Load(ScreenManager* ScreenManager);
	virtual void Update(ScreenManager* ScreenManager,sf::RenderWindow* Window,float DeltaT);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void Events(sf::Event Event);
	virtual bool Opaque(){return false;}
	virtual bool BlockUpdate(){return false;}

private:
	TextEntry mTestEntry;
	sf::Sprite mStuff;
	sf::RectangleShape mRect;

};

