#ifndef MOVABLE_OBJECT_M_H
#define MOVABLE_OBJECT_M_H

#include "GameObjectM.h"

enum Direction
{
	RIGHT = -2,
	TOP,
	BOTTOM = 1,
	LEFT

};

class MoveEventArgs
{
public:
	MoveEventArgs(XY _sourcePos, Direction _direct, sf::Time _time, StrongObjectPtr& _source);
	XY sourcePos;
	sf::Time time;
	Direction direct;
	StrongObjectPtr& source;
};

class MovableObjectM : public GameObjectM
{
public:
	MovableObjectM(ObjectType _type, XY _pos, SizeX _width, SizeY _height, float _velocity);

	float getVelocity();
	void setVelocity(float _velocity);

	void moveTo(sf::Time _time, Direction _direct);
	void moveRequest(sf::Time _time, Direction _direct);

	Event<MoveEventArgs> moveEvent;
	Event<MoveEventArgs> moveRequestEvent;
	XY getTargetPos(sf::Time _time, Direction _direct);
	static Direction invertDirection(Direction _direct);

private:
	float velocity_;
};


#endif // MOVABLE_OBJECT_M_H

