#ifndef LEVEL_M_H
#define LEVEL_M_H

#include <string>
#include <windows.h>
#include <iostream>

#include "WallM.h"
#include "PlayerM.h"
#include "ZombieM.h"
#include "OliveM.h"
#include "LightSourceM.h"
#include "TileField.h"
#include "TinyXML/tinyxml2.h"
#include <math.h>
#include "InterfaceDll.h"


typedef AIInterface*(*AICreation)();

#ifndef XMLCheckResult

#define XMLCheckResult(result)\
if (result != tinyxml2::XML_SUCCESS)\
{\
	throw;\
}
#endif // XMLCheckResult

class LevelM: public std::enable_shared_from_this<LevelM>
{
public:
	LevelM();
	~LevelM();

	void readMap(std::string _pathToMap);

	void moveMainPlayer(Direction _direct, sf::Time _time);
	void shootMainPlayer();

	void zombieMoveRequestHandler(MoveEventArgs _args);
	void oliveMoveRequestHandler(MoveEventArgs _args);
	void zombieAIRequestHandler(AIArgs _args);
	void playerShadowCheckHandler(StrongObjectPtr& _arg);

	void tickHandler(sf::Time _time);
	Event<sf::Time> tickEvent;
	Event<std::shared_ptr<ShadowM>&> shadowAddEvent;

	std::shared_ptr<TileField> tileField_;
	std::weak_ptr<PlayerM> mainPlayer_;

	std::vector<std::weak_ptr<GameObjectM>> lightStore;


	static const float defaultVelocity;

private:
	HINSTANCE hLib;
	std::unique_ptr<AIInterface, detail::AIInterfaceRelease> aiPtr;
	AICreation create;
};

#include "GMImplement\LevelM.hpp"
#endif // LEVEL_M_H