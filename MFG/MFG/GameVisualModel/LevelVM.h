#ifndef LEVEL_VM_H
#define LEVEL_VM_H

#include "GameObjectVM.h" 
#include "GameVisualModel\WallVM.h"
#include "GameVisualModel\PlayerVM.h"
#include "GameModel\LevelM.h"
#include "GameVisualModel\OliveVM.h"
#include "GameVisualModel\ZombieVM.h"
#include "ShadowVM.h"
#include <string>


class LevelVM: public std::enable_shared_from_this<LevelVM>
{
public:
	LevelVM();

	void loadModel(std::string _path);
	void updateModel(sf::Time _time);

	std::shared_ptr<LevelM> levelM_;
	std::map<ObjectID, std::shared_ptr<GameObjectVM>> gameObjectVMStore_;
	std::map<ObjectID, std::shared_ptr<ShadowVM>> shadowVMStore_;

	void playerShootHandler(std::shared_ptr<OliveM>& _arg);
	void objectDeleteHandler(ObjectID _args);
	void shadowDeleteHandler(ObjectID _args);
	void playerChangeHealthHandler(ProcentOfMaxHealth _arg);
	void playerDiedHandler(EmptyArg _arg);
	void shadowAddHandler(std::shared_ptr<ShadowM>& _arg);
	sf::Sprite getMainPlayer();

	Event<sf::Time> modelUpdateEvent;
	Event<ProcentOfMaxHealth> playerChangeHealthEvent;
	Event<EmptyArg> playerDiedEvent;

	sf::Texture playerMoveAnimTexture;
	sf::Texture zombieMoveAnimTexture;
	sf::Texture oliveMoveAnimTexture;
	sf::Texture wallTexture;
	sf::Texture playerShadowTexture;

private:

	sf::Sprite mainPlayer_;
};


#include "GVMImplement\LevelVM.hpp"

#endif // LEVEL_VM_H