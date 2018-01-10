
#include <stdexcept>
#include "stdafx.h"
#include "ZombieM.h"

AIArgs::AIArgs(sf::Time _time, std::shared_ptr<GameObjectM>& _source) :
	source_(_source),
	time_(_time)
{
}

const SizeX ZombieM::damageAreaWidth = 100;
const SizeY ZombieM::damageAreaHeight = 100;
const float ZombieM::damageMaxHealthProcent = 0.0001f;


ZombieM::ZombieM(XY _pos, SizeX _width, SizeY _height, float _velocity) :
	MovableObjectM(ZOMBIE, _pos, _width, _height, _velocity),
	viewDirect_(RIGHT)
{
}

ZombieM::~ZombieM()
{
}


void ZombieM::tickHandler(sf::Time _time)
{
	AIRequestEvent.invoke(AIArgs(_time, shared_from_this()));

}

Direction ZombieM::getViewDirection()
{
	return viewDirect_;
}
void ZombieM::setViewDirect(Direction _direct)
{
	viewDirect_ = _direct;
}