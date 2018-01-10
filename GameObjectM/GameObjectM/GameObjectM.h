#ifndef GAME_OBJECT_M_H
#define GAME_OBJECT_M_H

#include <vector>
#include <memory>
#include "Event.h"
#include "SFML/System/Time.hpp"
#include <map>

enum ObjectType
{
	AREA,
	PLAYER,
	WALL,
	OLIVE,
	ZOMBIE,
	LIGHT
};


typedef float X;
typedef float Y;
typedef float SizeX;
typedef float SizeY;
typedef int ObjectID;

class XY
{
public:
	XY(X _x, Y _y);
	XY(const XY& _that);
	const XY& operator=(const XY& _that);
	X x;
	Y y;
};

class ObjectRect
{
public:
	ObjectRect(XY _pos, SizeX _width, SizeY _height);
	ObjectRect(const ObjectRect& _that);
	const ObjectRect& operator=(const ObjectRect& _that);
	XY pos;
	SizeX width;
	SizeY height;
	bool isCrossed(ObjectRect _rect);
};

enum ShadowStatus
{
	EXPIRED,
	VALID
};

class ShadowM : public std::enable_shared_from_this<ShadowM>
{
public:
	ShadowM(ObjectID _lightID, float _angle, XY _pos);
	ShadowStatus status;
	float angle;
	XY pos;
	Event<std::shared_ptr<ShadowM>&> changeParamEvent;
	Event<ObjectID> deleteEvent;
	ObjectID lightID;
	XY lightPos;
	ObjectID id;
	~ShadowM();
private:
	static ObjectID currentId_;

};

class GameObjectM;

typedef GameObjectM* ObjectPtr;
typedef GameObjectM& ObjectRef;
typedef std::shared_ptr<GameObjectM> StrongObjectPtr;
typedef std::weak_ptr<GameObjectM> WeakObjectPtr;

class ChangePosArgs
{
public:
	ChangePosArgs(XY _sourcePos, XY _targetPos, StrongObjectPtr& _source);
	XY targetPos;
	XY sourcePos;
	StrongObjectPtr& source;
};

class GameObjectM : public std::enable_shared_from_this<GameObjectM>
{
public:
	GameObjectM(ObjectType _type, XY _pos, SizeX _width, SizeY _height);
	GameObjectM(const ObjectRef _that);
	virtual ~GameObjectM();

	ObjectType getType() const;
	ObjectRect& getObjectRect();
	ObjectID getId() const;

	void setPosition(XY _targetPos);

	Event<ObjectID> deleteEvent;
	Event<ChangePosArgs> changePosEvent;

	std::map<ObjectID, std::shared_ptr<ShadowM>> shadowStore;

	virtual void tickHandler(sf::Time _time);
private:
	static ObjectID currentId_;

protected:
	ObjectID id_;
	ObjectRect objRect_;
	ObjectType type_;
};



#endif // GAME_OBJECT_M_H
