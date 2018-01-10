#include <stdexcept>
#include "stdafx.h"
#include "GameObjectM.h"


const XY& XY::operator=(const XY& _that)
{
	if (&_that == this)
		return *this;
	x = _that.x;
	y = _that.y;
	return *this;
}



XY::XY(X _x = 0, Y _y = 0) : x(_x), y(_y)
{
}

XY::XY(const XY& _that)
{
	x = _that.x;
	y = _that.y;
}

ObjectRect::ObjectRect(XY _pos = XY(0, 0), SizeX _width = 0, SizeY _height = 0) :pos(_pos), width(_width), height(_height)
{

}
ObjectRect::ObjectRect(const ObjectRect& _that)
{
	pos = _that.pos;
	width = _that.width;
	height = _that.height;
}

const ObjectRect& ObjectRect::operator=(const ObjectRect& _that)
{
	if (&_that == this)
	{
		return *this;
	}
	pos = _that.pos;
	width = _that.width;
	height = _that.height;
	return *this;
}

bool ObjectRect::isCrossed(ObjectRect _rect)
{
	X myCenterX = pos.x + width / 2;
	Y myCenterY = pos.y + height / 2;
	X targetCenterX = _rect.pos.x + _rect.width / 2;
	Y targetCenterY = _rect.pos.y + _rect.height / 2;;

	if (abs(myCenterX - targetCenterX) > (width / 2 + _rect.width / 2) ||
		abs(myCenterY - targetCenterY) > (height / 2 + _rect.height / 2)
		)
	{
		return false;
	}
	return true;
}

ObjectRect& GameObjectM::getObjectRect()
{
	return objRect_;
}

int GameObjectM::currentId_ = 0;
int ShadowM::currentId_ = 0;

GameObjectM::GameObjectM(ObjectType _type, XY _pos, SizeX _width, SizeY _height) :
	type_(_type),
	objRect_(_pos, _width, _height),
	id_(currentId_)
{
	++currentId_;
}

ChangePosArgs::ChangePosArgs(XY _sourcePos, XY _targetPos, StrongObjectPtr& _source) : sourcePos(_sourcePos), targetPos(_targetPos), source(_source)
{

}

int GameObjectM::getId() const
{
	return id_;
}


ObjectType GameObjectM::getType() const
{
	return type_;
}

GameObjectM::~GameObjectM()
{
	deleteEvent.invoke(id_);
}

GameObjectM::GameObjectM(const ObjectRef _that)
{
	objRect_ = _that.objRect_;
	type_ = _that.type_;
	id_ = _that.id_;
}

void GameObjectM::setPosition(XY _targetPos)
{
	XY sourcePos = objRect_.pos;
	objRect_.pos = _targetPos;

	changePosEvent.invoke(ChangePosArgs(sourcePos, objRect_.pos, shared_from_this()));

}

void GameObjectM::tickHandler(sf::Time _time)
{

}

ShadowM::ShadowM(ObjectID _lightID, float _angle, XY _pos) : angle(_angle), pos(_pos), lightID(_lightID), status(VALID), id(currentId_)
{
	++currentId_;
}

ShadowM::~ShadowM()
{
	deleteEvent.invoke(id);
}