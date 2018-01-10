#ifndef LEVEL_VM_HPP
#define LEVEL_VM_HPP



void LevelVM::objectDeleteHandler(ObjectID _args)
{
	gameObjectVMStore_.erase(_args);
}
void LevelVM::shadowDeleteHandler(ObjectID _args)
{
	shadowVMStore_.erase(_args);
}

void LevelVM::playerChangeHealthHandler(ProcentOfMaxHealth _arg)
{
	playerChangeHealthEvent.invoke(_arg);
}

void LevelVM::shadowAddHandler(std::shared_ptr<ShadowM>& _arg)
{
	sf::Sprite sprite;
	sprite.setTexture(playerShadowTexture);
	sprite.setOrigin(0, 21);
	sprite.setPosition(_arg->pos.x, _arg->pos.y);
	sprite.setRotation(_arg->angle * 180 / 3.14f);
	std::shared_ptr<ShadowVM> shadow = std::make_shared<ShadowVM>(sprite);
	_arg->changeParamEvent.Add(shadow, &ShadowVM::propChangedHandler);
	_arg->deleteEvent.Add(shared_from_this(), &LevelVM::shadowDeleteHandler);
	shadowVMStore_.insert(std::pair<ObjectID, std::shared_ptr<ShadowVM>>(_arg->id, shadow));
}

sf::Sprite LevelVM::getMainPlayer()
{
	return mainPlayer_;
}

void LevelVM::loadModel(std::string _path)
{
	levelM_ = std::make_shared<LevelM>();
	modelUpdateEvent.Add(levelM_, &LevelM::tickHandler);
	levelM_->shadowAddEvent.Add(shared_from_this(), &LevelVM::shadowAddHandler);
	levelM_->readMap(_path);
	for (std::pair<ObjectID, StrongObjectPtr> pair : levelM_->tileField_->gameObjectStore_)
	{
		switch (pair.second->getType())
		{
		case  PLAYER: 
						{
							PlayerM* playerM = (PlayerM*)pair.second.get();
							sf::Sprite sprite;
							sprite.setTexture(playerMoveAnimTexture);
							std::shared_ptr<PlayerVM> player = std::make_shared<PlayerVM>(sprite, playerM->getObjectRect());

							mainPlayer_ = sprite;
							player->moveAnimation.loadTexture(&playerMoveAnimTexture, 3);
							player->moveAnimation.play(player->getSprite(), sf::Time::Zero);

							gameObjectVMStore_.insert(std::pair<ObjectID, std::shared_ptr<GameObjectVM>>(playerM->getId(), player));
							playerM->deleteEvent.Add(shared_from_this(), &LevelVM::objectDeleteHandler);
							playerM->moveEvent.Add(player, &PlayerVM::moveHandler);
							playerM->shootEvent.Add(shared_from_this(), &LevelVM::playerShootHandler);
							playerM->healthChangedEvent.Add(shared_from_this(), &LevelVM::playerChangeHealthHandler);
							playerM->youDiedEvent.Add(shared_from_this(), &LevelVM::playerDiedHandler);
						}break;
		case  ZOMBIE:	{
							ZombieM* zombieM = (ZombieM*)pair.second.get();
							sf::Sprite sprite;
							sprite.setTexture(zombieMoveAnimTexture);
							std::shared_ptr<ZombieVM> zombie = std::make_shared<ZombieVM>(sprite, zombieM->getObjectRect());
							zombie->moveAnimation.loadTexture(&zombieMoveAnimTexture, 2);
							zombie->moveAnimation.play(zombie->getSprite(), sf::Time::Zero);
							gameObjectVMStore_.insert(std::pair<ObjectID, std::shared_ptr<GameObjectVM>>(zombieM->getId(), zombie));
							zombieM->deleteEvent.Add(shared_from_this(), &LevelVM::objectDeleteHandler);
							zombieM->moveEvent.Add(zombie, &ZombieVM::moveHandler);
						}break;
		case  WALL: 
					{
						/*WallM* wallM = (WallM*)pair.second.get();
						sf::Sprite sprite;
						sprite.setTexture(wallTexture);
						std::shared_ptr<WallVM> wall = std::make_shared<WallVM>(sprite, wallM->getObjectRect());
						gameObjectVMStore_.insert(std::pair<ObjectID, std::shared_ptr<GameObjectVM>>(wallM->getId(), wall));
						wallM->deleteEvent.Add(shared_from_this(), &LevelVM::objectDeleteHandler);*/
					}break;
		}
	}

}



LevelVM::LevelVM() 
{
	playerMoveAnimTexture.loadFromFile("GameObjectTextures/player.png");
	zombieMoveAnimTexture.loadFromFile("GameObjectTextures/zombie.png");
	oliveMoveAnimTexture.loadFromFile("GameObjectTextures/olive.png");
	wallTexture.loadFromFile("GameObjectTextures/wall.png");
	playerShadowTexture.loadFromFile("GameObjectTextures/shadow.png");
}

void LevelVM::playerDiedHandler(EmptyArg _arg)
{
	playerDiedEvent.invoke(_arg);
}

void LevelVM::playerShootHandler(std::shared_ptr<OliveM>& _arg)
{
	OliveM* oliveM = (OliveM*)_arg.get();
	sf::Sprite sprite;
	switch (oliveM->flyDirect_)
	{
	case RIGHT: {
					sprite.setScale(1, 1);
				}break;
	case LEFT:	{
					sprite.setScale(-1, 1);
				}break;
	case TOP:	{
					sprite.setRotation(-90);
				}break;
	case BOTTOM:
				{
					sprite.setRotation(90);
				}break;
	}
	sprite.setTexture(oliveMoveAnimTexture);
	std::shared_ptr<OliveVM> olive = std::make_shared<OliveVM>(sprite, oliveM->getObjectRect());
	
	olive->moveAnimation.loadTexture(&oliveMoveAnimTexture, 2);
	olive->moveAnimation.play(olive->getSprite(), sf::Time::Zero);
	gameObjectVMStore_.insert(std::pair<ObjectID, std::shared_ptr<GameObjectVM>>(oliveM->getId(), olive));
	oliveM->moveEvent.Add(olive, &OliveVM::moveHandler);
	oliveM->deleteEvent.Add(shared_from_this(), &LevelVM::objectDeleteHandler);
}



void LevelVM::updateModel(sf::Time _time)
{
	modelUpdateEvent.invoke(_time);
}

#endif // LEVEL_VM_HPP