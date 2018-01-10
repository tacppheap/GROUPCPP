#ifndef ZOMBIE_VM_H
#define ZOMBIE_VM_H

#include "GameObjectVM.h" 
#include "ZombieM.h"
#include "Animation.h"

class ZombieVM : public GameObjectVM
{
public:
	ZombieVM(sf::Sprite _sprite, ObjectRect _rect);
	~ZombieVM() override = default;

	void moveHandler(MoveEventArgs _args);
	Animation moveAnimation;



};



#include "GVMImplement\ZombieVM.hpp"
#endif // ZOMBIE_VM_H
