#ifndef ZOMBIE_M_H
#define ZOMBIE_M_H

#include "MovableObjectM.h"


class AIArgs
{
public:
	AIArgs(sf::Time _time, std::shared_ptr<GameObjectM>& _source);
	std::shared_ptr<GameObjectM>& source_;
	sf::Time time_;
};

class ZombieM : public MovableObjectM
{
public:
	ZombieM(XY _pos, SizeX _width, SizeY _height, float _velocity);
	~ZombieM() override;

	Event<AIArgs> AIRequestEvent;

	void tickHandler(sf::Time _time) override;

	Direction getViewDirection();
	void setViewDirect(Direction _direct);

	static const SizeX damageAreaWidth;
	static const SizeY damageAreaHeight;
	static const float damageMaxHealthProcent;

private:
	Direction viewDirect_;
};

#endif // ZOMBIE_M_H
