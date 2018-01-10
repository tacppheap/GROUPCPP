#ifndef LEVEL_M_HPP
#define LEVEL_M_HPP


Direction internalZombieAI(TileField* _tileField, ZombieM* _zombie)
{
	return _zombie->getViewDirection();
}

const float LevelM::defaultVelocity = 0.2f;

void getXMLParam(tinyxml2::XMLElement* _mapElem, float& _x, float& _y, float& _objWidth, float& _objHeight)
{
	_mapElem->QueryFloatAttribute("x", &_x);
	_mapElem->QueryFloatAttribute("y", &_y);
	_mapElem->QueryFloatAttribute("width", &_objWidth);
	_mapElem->QueryFloatAttribute("height", &_objHeight);
}

void LevelM::tickHandler(sf::Time _time)
{
	tickEvent.invoke(_time);
	PlayerM* player = mainPlayer_.lock().get();
	ObjectRect damageObjRect = player->getObjectRect();
	damageObjRect.height = ZombieM::damageAreaHeight;
	damageObjRect.width = ZombieM::damageAreaWidth;
	damageObjRect.pos.x -= (ZombieM::damageAreaWidth - player->getObjectRect().width) / 2;
	damageObjRect.pos.y -= (ZombieM::damageAreaHeight - player->getObjectRect().height) / 2;

	if (tileField_->selectCrossedObj(AREA, damageObjRect, player->getId(), std::vector<ObjectType>{ZOMBIE}).size() != 0)
	{
		player->setHealth(player->getHealth() - player->getMaxHealth() * ZombieM::damageMaxHealthProcent);
	}
}

void LevelM::readMap(std::string _pathToMap)
{

	tinyxml2::XMLDocument mapDoc;
	tinyxml2::XMLError XMLResult = mapDoc.LoadFile(&_pathToMap[0]);
	XMLCheckResult(XMLResult);

	int tileWidth;
	int tileHeight;
	int width;
	int height;

	tinyxml2::XMLElement* mapRootElem = mapDoc.RootElement();
	if (mapRootElem == nullptr) throw;
	tinyxml2::XMLElement* mapElem = mapRootElem;

	XMLResult = mapElem->QueryIntAttribute("tilewidth", &tileWidth);
	XMLCheckResult(XMLResult);
	XMLResult = mapElem->QueryIntAttribute("tileheight", &tileHeight);
	XMLCheckResult(XMLResult);
	XMLResult = mapElem->QueryIntAttribute("height", &height);
	XMLCheckResult(XMLResult);
	XMLResult = mapElem->QueryIntAttribute("width", &width);
	XMLCheckResult(XMLResult);

	tileField_ = std::make_shared<TileField>(width, height, tileWidth, tileHeight);

	mapElem = mapRootElem->FirstChildElement("objectgroup");
	if (mapElem == nullptr) throw;

	tinyxml2::XMLElement* rootWallObj = nullptr;
	tinyxml2::XMLElement* rootPlayerObj = nullptr;
	tinyxml2::XMLElement* rootZombieObj = nullptr;
	tinyxml2::XMLElement* rootLightObj = nullptr;

	while (mapElem != nullptr)
	{
		const char* AttributeText = nullptr;
		AttributeText = mapElem->Attribute("name");
		std::string objectgroupName = AttributeText;
		if (objectgroupName == "walls")
		{
			rootWallObj = mapElem;
		}

		if (objectgroupName == "players")
		{
			rootPlayerObj = mapElem;
		}

		if (objectgroupName == "zombies")
		{
			rootZombieObj = mapElem;
		}

		if (objectgroupName == "lights")
		{
			rootLightObj = mapElem;
		}

		mapElem = mapElem->NextSiblingElement("objectgroup");
	}

	if (!rootPlayerObj) throw;

	tinyxml2::XMLElement* wallElem = rootWallObj->FirstChildElement("object");
	tinyxml2::XMLElement* playerElem = rootPlayerObj->FirstChildElement("object");
	tinyxml2::XMLElement* zombieElem = rootZombieObj->FirstChildElement("object");
	tinyxml2::XMLElement* lightElem = rootLightObj->FirstChildElement("object");

	float x = 0;
	float y = 0;
	float objWidth = 0;
	float objHeight = 0;

	while (wallElem != nullptr)
	{
		getXMLParam(wallElem, x, y, objWidth, objHeight);
		std::shared_ptr<WallM> wall = std::make_shared<WallM>(XY(x, y),
																objWidth,
																objHeight);

		tileField_->addObject(std::static_pointer_cast<GameObjectM>(wall));

		wallElem = wallElem->NextSiblingElement("object");
	}
	/*********************************************************************************************************/

	getXMLParam(playerElem, x, y, objWidth, objHeight);
	std::shared_ptr<PlayerM> player = std::make_shared<PlayerM>(	XY(x, y),
																	objWidth,
																	objHeight,
																	defaultVelocity);

	tileField_->addObject(std::static_pointer_cast<GameObjectM>(player));
	tileField_->addObject(std::static_pointer_cast<GameObjectM>(player->electricLight));
	lightStore.push_back(std::static_pointer_cast<GameObjectM>(player->electricLight));
	player->shadowCheckEvent.Add(shared_from_this(), &LevelM::playerShadowCheckHandler);
	tickEvent.Add(player, &PlayerM::tickHandler);
	mainPlayer_ = player;
	/*********************************************************************************************************/

	while (zombieElem != nullptr)
	{
		getXMLParam(zombieElem, x, y, objWidth, objHeight);
		std::shared_ptr <ZombieM> zombie = std::make_shared<ZombieM>(	XY(x, y),
																		objWidth,
																		objHeight,
																		0.7f*defaultVelocity);
		tileField_->addObject(std::static_pointer_cast<GameObjectM>(zombie));
		tickEvent.Add(zombie, &ZombieM::tickHandler);

		zombie->AIRequestEvent.Add(shared_from_this(), &LevelM::zombieAIRequestHandler);
		zombie->moveRequestEvent.Add(shared_from_this(), &LevelM::zombieMoveRequestHandler);

		zombieElem = zombieElem->NextSiblingElement("object");
	}
	/*********************************************************************************************************/

	while (lightElem != nullptr)
	{
		getXMLParam(lightElem, x, y, objWidth, objHeight);

		int lightX;
		int lightY;
		tinyxml2::XMLElement* lightRootProp = lightElem->FirstChildElement("properties");
		tinyxml2::XMLElement* lightProp = lightRootProp->FirstChildElement("property");
		const char* attributeText = nullptr;
		std::string name = "";

		while (lightProp != nullptr)
		{
			attributeText = lightProp->Attribute("name");
			name = attributeText;
			if (name == "lightX")
			{
				lightProp->QueryIntAttribute("value", &lightX);
			}
			else
			{
				lightProp->QueryIntAttribute("value", &lightY);
			}
			lightProp = lightProp->NextSiblingElement("property");
		}
		

		std::shared_ptr<LightSourceM> light = std::make_shared<LightSourceM>(XY(x, y),
			objWidth,
			objHeight,
			XY(lightX, lightY));
		tileField_->addObject(std::static_pointer_cast<GameObjectM>(light));

		lightElem = lightElem->NextSiblingElement("object");
	}

}

LevelM::LevelM()
{

	hLib = LoadLibrary(TEXT("InterfaceDll.dll"));
	if (hLib == NULL)
	{
		printf("Unable to load the library 'InterfaceDll.dll'!\n");
		throw;
	}
	else
	{
		create = (AICreation)GetProcAddress(hLib, "createAI");

		aiPtr = std::move(std::unique_ptr<AIInterface,detail::AIInterfaceRelease>(create()));
		if (!aiPtr)
		{
			printf("Unable to find the function 'zombieAI'!\n\n");
			throw;
		}
	}
}

LevelM::~LevelM()
{
}


void LevelM::zombieMoveRequestHandler(MoveEventArgs _args)
{
	ZombieM* zombie = (ZombieM*)_args.source.get();
	ObjectRect targetObjRect = zombie->getObjectRect();
	targetObjRect.pos = zombie->getTargetPos(_args.time, _args.direct);
	if (targetObjRect.pos.x < 0 ||
		targetObjRect.pos.y < 0 ||
		targetObjRect.pos.x > tileField_->getWidth() * tileField_->getTileWidth() ||
		targetObjRect.pos.y > tileField_->getHeight() * tileField_->getTileHeight())
	{
		zombie->setViewDirect(MovableObjectM::invertDirection(zombie->getViewDirection()));
	}

	if (tileField_->selectCrossedObj(ZOMBIE, targetObjRect, zombie->getId(), std::vector<ObjectType>{WALL, ZOMBIE}).size() != 0)
	{
		zombie->setViewDirect(MovableObjectM::invertDirection(zombie->getViewDirection()));
		return;
	}

	if (tileField_->selectCrossedObj(ZOMBIE, targetObjRect, zombie->getId(), std::vector<ObjectType>{PLAYER}).size() != 0)
	{
		zombie->setViewDirect(MovableObjectM::invertDirection(zombie->getViewDirection()));
		return;
	}



	zombie->moveTo(_args.time, _args.direct);
	
}

void LevelM::oliveMoveRequestHandler(MoveEventArgs _args)
{
	OliveM* olive = (OliveM*)_args.source.get();
	ObjectRect targetObjRect = olive->getObjectRect();
	targetObjRect.pos = olive->getTargetPos(_args.time, _args.direct);

	std::vector<StrongObjectPtr> crossedObj = tileField_->selectCrossedObj(	OLIVE,
																			targetObjRect,
																			olive->getId(),
																			std::vector<ObjectType>{WALL, ZOMBIE, PLAYER});

	if (crossedObj.size() == 0)
	{
		olive->moveTo(_args.time, _args.direct);

		LightSourceM* light = (LightSourceM*)olive->electricLight.get();
		ObjectRect lightTargetObjRect = light->getObjectRect();
		lightTargetObjRect.pos = XY(targetObjRect.pos.x - (OliveM::oliveDefaultElectricLightWidth - targetObjRect.width) / 2,
			targetObjRect.pos.y - (OliveM::oliveDefaultElectricLightHeight - targetObjRect.height) / 2);

			olive->electricLight->setPosition(lightTargetObjRect.pos);

		olive->electricLight->lightPos = XY(targetObjRect.pos.x + targetObjRect.width / 2, targetObjRect.pos.y + targetObjRect.height / 2);
	}
	else
	{
		tileField_->deleteObject(olive);
		tileField_->deleteObject(olive->electricLight.get());
		for (StrongObjectPtr& obj : crossedObj)
		{
			if (obj->getType() == ZOMBIE)
			{
				tileField_->deleteObject(obj.get());
			}
		}

	}
}


void  LevelM::zombieAIRequestHandler(AIArgs _args)
{
	ZombieM* zombie = (ZombieM*)_args.source_.get();
	ObjectRect targetObjRect = zombie->getObjectRect();
	

		zombie->moveRequest(_args.time_, aiPtr->AIRequestHandler(tileField_.get(), zombie));

		targetObjRect = zombie->getObjectRect();
		std::vector<StrongObjectPtr> lightObjs = tileField_->selectCrossedObj(ZOMBIE, targetObjRect, zombie->getId(), std::vector<ObjectType>{LIGHT});
		std::map<ObjectID, std::shared_ptr<ShadowM>>::iterator it;
		for (std::pair<ObjectID, std::shared_ptr<ShadowM>> pair : zombie->shadowStore)
		{
			pair.second->status = EXPIRED;
		}

		float angle = 0;
		XY pos(0,0);

		if (lightObjs.size() > 0)
		{
			for (StrongObjectPtr& lightObj : lightObjs)
			{
				it = zombie->shadowStore.find(lightObj->getId());
				LightSourceM* light = (LightSourceM*)(lightObj.get());
				pos = XY(zombie->getObjectRect().pos.x + zombie->getObjectRect().width / 2,
					zombie->getObjectRect().pos.y + zombie->getObjectRect().height / 2);

				angle = std::atan2(pos.y - light->lightPos.y,
					pos.x - light->lightPos.x);


				if (it != zombie->shadowStore.end())
				{
					it->second->angle = angle;
					it->second->pos = pos;
					it->second->status = VALID;
					it->second->lightPos = light->lightPos;
					it->second->changeParamEvent.invoke(it->second);
				}
				else
				{
					std::shared_ptr<ShadowM> shadow = std::make_shared<ShadowM>(lightObj->getId(), angle, pos);
					shadow->lightPos = light->lightPos;
					zombie->shadowStore.insert(std::pair<ObjectID, std::shared_ptr<ShadowM>>(lightObj->getId(), shadow));
					shadowAddEvent.invoke(shadow);
				}
			}
		}
		for (std::pair<ObjectID, std::shared_ptr<ShadowM>> pair : zombie->shadowStore)
		{
			if (pair.second->status == EXPIRED)
			{
				zombie->shadowStore.erase(pair.second->lightID);
			}
		}

}

void LevelM::playerShadowCheckHandler(StrongObjectPtr& _arg)
{

	PlayerM* player = mainPlayer_.lock().get();
	ObjectRect targetObjRect = player->getObjectRect();

	std::vector<StrongObjectPtr> lightObjs = tileField_->selectCrossedObj(PLAYER, targetObjRect, player->getId(), std::vector<ObjectType>{LIGHT});
	std::map<ObjectID, std::shared_ptr<ShadowM>>::iterator it;
	for (std::pair<ObjectID, std::shared_ptr<ShadowM>> pair : player->shadowStore)
	{
		pair.second->status = EXPIRED;
	}

	float angle = 0;
	XY pos(0,0);

	if (lightObjs.size() > 0)
	{
		for (StrongObjectPtr& lightObj : lightObjs)
		{
			it = player->shadowStore.find(lightObj->getId());
			LightSourceM* light = (LightSourceM*)(lightObj.get());
			pos = XY(player->getObjectRect().pos.x + player->getObjectRect().width / 2,
				player->getObjectRect().pos.y + player->getObjectRect().height / 2);

			angle = std::atan2(pos.y - light->lightPos.y,
				pos.x - light->lightPos.x);


			if (it != player->shadowStore.end())
			{
				it->second->angle = angle;
				it->second->pos = pos;
				it->second->status = VALID;
				it->second->lightPos = light->lightPos;
				it->second->changeParamEvent.invoke(it->second);

			}
			else
			{
				std::shared_ptr<ShadowM> shadow = std::make_shared<ShadowM>(lightObj->getId(), angle, pos);
				shadow->lightPos = light->lightPos;
				player->shadowStore.insert(std::pair<ObjectID, std::shared_ptr<ShadowM>>(lightObj->getId(), shadow));
				shadowAddEvent.invoke(shadow);
			}
		}
	}
	for (std::pair<ObjectID, std::shared_ptr<ShadowM>> pair : player->shadowStore)
	{
		if (pair.second->status == EXPIRED)
		{
			player->shadowStore.erase(pair.second->lightID);
		}
	}
}

void  LevelM::shootMainPlayer()
{


	PlayerM* player = mainPlayer_.lock().get();

	if (player->getCurrentShootCooldown() > sf::Time::Zero)
	{
		return;
	}

	ObjectRect playerObjRect = player->getObjectRect();
	std::shared_ptr<OliveM> olive = std::make_shared<OliveM>(	
																XY(player->getObjectRect().pos.x, player->getObjectRect().pos.y),
																OliveM::oliveDefaultWidth,
																OliveM::oliveDefaultHeight,
																2*defaultVelocity,
																RIGHT);

	switch (player->getViewDirect())
	{
	case RIGHT: {
					olive->getObjectRect().pos = XY(playerObjRect.pos.x + playerObjRect.width + OliveM::oliveDefaultWidth / 3 ,
													playerObjRect.pos.y);
				}break;
	case LEFT:  {
					olive->getObjectRect().pos = XY(playerObjRect.pos.x - OliveM::oliveDefaultWidth/0.8f,
													playerObjRect.pos.y);
					olive->flyDirect_ = LEFT;
				}break;
	case TOP:  {
					olive->getObjectRect().pos = XY(playerObjRect.pos.x,
													playerObjRect.pos.y - OliveM::oliveDefaultHeight/ 0.8f);
					olive->flyDirect_ = TOP;
				}break;
	case BOTTOM: {
					olive->getObjectRect().pos = XY(playerObjRect.pos.x,
													playerObjRect.pos.y + playerObjRect.height + OliveM::oliveDefaultHeight /3);
					olive->flyDirect_ = BOTTOM;
				 }break;

	}

	tileField_->addObject(std::static_pointer_cast<GameObjectM>(olive));
	tileField_->addObject(std::static_pointer_cast<GameObjectM>(olive->electricLight));
	lightStore.push_back(std::static_pointer_cast<GameObjectM>(olive->electricLight));
	olive->moveRequestEvent.Add(shared_from_this(), &LevelM::oliveMoveRequestHandler);
	tickEvent.Add(olive, &OliveM::tickHandler);
	player->shoot(olive);
}

void LevelM::moveMainPlayer(Direction _direct, sf::Time _time)
{
	PlayerM* player = mainPlayer_.lock().get();
	ObjectRect targetObjRect = player->getObjectRect();
	targetObjRect.pos = player->getTargetPos(_time, _direct);

	if (tileField_->selectCrossedObj(PLAYER, targetObjRect, player->getId(),  std::vector<ObjectType>{WALL, ZOMBIE}).size() == 0)
	{
		player->moveTo(_time, _direct);
		player->viewDirect_ = _direct;

		LightSourceM* light = (LightSourceM*)player->electricLight.get();
		ObjectRect lightTargetObjRect = light->getObjectRect();
		lightTargetObjRect.pos = XY(targetObjRect.pos.x - (PlayerM::defaultElectricLightWidth - targetObjRect.width) / 2,
			targetObjRect.pos.y - (PlayerM::defaultElectricLightHeight - targetObjRect.height) / 2);;

		//if (tileField_->selectCrossedObj(LIGHT, lightTargetObjRect, player->electricLight->getId(), std::vector<ObjectType>{WALL}).size() == 0)
		//{
			player->electricLight->setPosition(lightTargetObjRect.pos);
		//}
		player->electricLight->lightPos = XY(targetObjRect.pos.x + targetObjRect.width / 2, targetObjRect.pos.y + targetObjRect.height / 2);

	}

	
}


#endif // LEVEL_M_HPP
