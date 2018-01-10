#ifndef WALL_VM_H
#define WALL_VM_H

#include "GameObjectVM.h" 
#include "GameModel\WallM.h"

class WallVM : public GameObjectVM 
{
public:
	WallVM(sf::Sprite _sprite, ObjectRect _rect);
	~WallVM() override = default;

};
#include "GVMImplement\WallVM.hpp"

#endif // WALL_VM_H