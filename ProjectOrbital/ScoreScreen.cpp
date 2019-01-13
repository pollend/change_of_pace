#include "ScoreScreen.h"
#include <sstream>

ScoreScreen::ScoreScreen(ClientManager* ClientManager)
{
	mClientManager = ClientManager;
}


ScoreScreen::~ScoreScreen(void)
{
}

void ScoreScreen::Load(ScreenManager* ScreenManager)
{
	if(mFont.loadFromFile("Assets//press.ttf"))
	mText.setFont(mFont);

	mText.setColor(sf::Color::Red);
}
void ScoreScreen::Update(ScreenManager* ScreenManager,sf::RenderWindow* Window,float DeltaT)
{
	sf::Packet* lPacket= mClientManager->GetPacket(SevenScorePacket::getPacketID());
	if(lPacket != NULL)
	{
		SevenScorePacket lScorePacket = SevenScorePacket(lPacket);
		mScoreObject = lScorePacket.getScoreObjects();
	}
}
void ScoreScreen::Draw(sf::RenderWindow* Window)
{
	for(int x = 0; x < mScoreObject.size(); x++)
	{
		std::stringstream lOStringStream;
		lOStringStream<< mScoreObject[x].getName() << "    " <<mScoreObject[x].getTime() ;
		mText.setString(lOStringStream.str());
		mText.setPosition(0,x*5);
		mText.setScale(.4f,.4f);
		Window->draw(mText);
	}
}
void ScoreScreen::Events(sf::Event Event)
{
}