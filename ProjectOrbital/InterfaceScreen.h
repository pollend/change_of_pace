#pragma once
#include "IScreen.h"
class InterfaceScreen :public IScreen
{
public:
	InterfaceScreen(void);
	~InterfaceScreen(void);

	virtual void Load(ScreenManager* ScreenManager);
	virtual void Update(ScreenManager* ScreenManager,sf::RenderWindow* Window,float DeltaT);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void Events(sf::Event Event);
	virtual bool Opaque(){return false;}
	virtual bool BlockUpdate(){return false;}
};

