// InterfaceDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "InterfaceDll.h"

#include <iostream>

class ZombieAI
	: public AIInterface
{
public:
	X viewW = 400;
	Y viewH = 400;

	void release() override
	{
		delete this;
	}
	ZombieAI()
	{
		std::cout << "created";
	}
	~ZombieAI() override
	{
		std::cout << "deleted";
	}

	Direction AIRequestHandler(TileField* _tileField, ZombieM* zombie) override
	{

		ObjectRect targetObjRect = zombie->getObjectRect();
		targetObjRect.pos = XY(	targetObjRect.pos.x - (viewW - targetObjRect.width) / 2,
								targetObjRect.pos.y - (viewH - targetObjRect.height) / 2);
		targetObjRect.width = viewW;
		targetObjRect.height = viewH;

		std::vector<StrongObjectPtr> selectedObj = _tileField->selectCrossedObj(ZOMBIE,
			targetObjRect,
			zombie->getId(),
			std::vector<ObjectType>{PLAYER});

		if (selectedObj.size() != 0)
		{
			StrongObjectPtr player = selectedObj[0];
			float dx = zombie->getObjectRect().pos.x - player->getObjectRect().pos.x;
			float dy = zombie->getObjectRect().pos.y - player->getObjectRect().pos.y;
			if (abs(dx) > abs(dy))
			{
				if (dx >= 0)
				{
					return LEFT;
				}
				else
				{
					return RIGHT;
				}
			}
			else
			{
				if (dy >= 0)
				{
					return TOP;
				}
				else
				{
					return BOTTOM;
				}

			}
		}

		return zombie->getViewDirection();
	}
};

AIInterface * createAI()
{
	return new ZombieAI();
}



