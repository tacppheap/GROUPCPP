#include <stdexcept>
#include "stdafx.h"
#include "MovableObjectM.h"

MoveEventArgs::MoveEventArgs(XY _sourcePos, Direction _direct, sf::Time _time, StrongObjectPtr& _source) :
	time(_time),
	direct(_direct),
	sourcePos(_sourcePos),
	source(_source)

{

}

Direction MovableObjectM::invertDirection(Direction _direct)
{
	return (Direction)((int)_direct * (-1));
}

MovableObjectM::MovableObjectM(ObjectType _type, XY _pos, SizeX _width, SizeY _height, float _velocity) :
	GameObjectM(_type, _pos, _width, _height),
	velocity_(_velocity)
{

}

void MovableObjectM::setVelocity(float _velocity)
{
	velocity_ = _velocity;
}

XY MovableObjectM::getTargetPos(sf::Time _time, Direction _direct)
{
	switch (_direct)
	{
	case RIGHT:
	{
		return XY(objRect_.pos.x + velocity_ * _time.asMilliseconds(), objRect_.pos.y);

	}break;
	case LEFT:
	{
		return	XY(objRect_.pos.x - velocity_ * _time.asMilliseconds(), objRect_.pos.y);

	}break;
	case TOP:
	{
		return	XY(objRect_.pos.x, objRect_.pos.y - velocity_ * _time.asMilliseconds());
	}break;
	case BOTTOM:
	{
		return XY(objRect_.pos.x, objRect_.pos.y + velocity_ * _time.asMilliseconds());
	}break;

	}
}

void MovableObjectM::moveRequest(sf::Time _time, Direction _direct)
{
	moveRequestEvent.invoke(MoveEventArgs(getObjectRect().pos, _direct, _time, shared_from_this()));
}

void MovableObjectM::moveTo(sf::Time _time, Direction _direct)
{
	moveEvent.invoke(MoveEventArgs(getObjectRect().pos, _direct, _time, shared_from_this()));
	setPosition(getTargetPos(_time, _direct));
}

float MovableObjectM::getVelocity()
{
	return velocity_;
}


