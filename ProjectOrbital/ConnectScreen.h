#pragma once
#include "IScreen.h"
#include "TextureManager.h"
#include "Btn.h"
#include "Map.h"
#include "TextEntry.h"
class ConnectScreen : public IScreen
{
private:
	Btn mClientButton;
	Btn mServerButton;
	sf::Sprite mTitleSprite;
	Map mMap;
	sf::Clock* mTime;
	TextEntry mIP;
public:
	ConnectScreen(void);
	~ConnectScreen(void);

	
	virtual void Load(ScreenManager* ScreenManager);
	virtual void Update(ScreenManager* ScreenManager,sf::RenderWindow* Window,float DeltaT);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void Events(sf::Event Event);
	virtual bool Opaque(){return false;}
	virtual bool BlockUpdate(){return false;}
};

