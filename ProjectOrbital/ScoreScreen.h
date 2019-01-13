#pragma once
#include "IScreen.h"
#include "ClientManager.h"
#include "ScoreObject.h"
#include "SevenScorePacket.h"
class ScoreScreen : public IScreen
{
private: 
	sf::Text mText;
	sf::Font mFont;

	ClientManager* mClientManager;
	std::vector<ScoreObject> mScoreObject;
public:
	ScoreScreen(ClientManager* ClientManager);
	~ScoreScreen(void);

	virtual void Load(ScreenManager* ScreenManager);
	virtual void Update(ScreenManager* ScreenManager,sf::RenderWindow* Window,float DeltaT);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void Events(sf::Event Event);
	virtual bool Opaque(){return false;}
	virtual bool BlockUpdate(){return false;}
};

