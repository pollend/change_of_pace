#include "ScoreObject.h"
ScoreObject::ScoreObject(void)
{

}

ScoreObject::ScoreObject(float Time, std::string Name)
{
	mTime = Time;
	mName = Name;
}

ScoreObject::~ScoreObject(void)
{
}
