#ifndef PLAYER_VM_H
#define PLAYER_VM_H

#include "Animation.h"
#include "GameModel\PlayerM.h"
#include "GameObjectVM.h"

class PlayerVM: public GameObjectVM
{
public:
	PlayerVM(sf::Sprite _sprite, ObjectRect _rect);
	~PlayerVM() override = default;

	void moveHandler(MoveEventArgs _args);

	Animation moveAnimation;
};



#include "GVMImplement\PlayerVM.hpp"
#endif // PLAYER_VM_H
