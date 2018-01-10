#ifndef OLIVE_VM_H
#define OLIVE_VM_H

#include "Animation.h"
#include "GameObjectVM.h" 
#include "GameModel\OliveM.h"


class OliveVM: public GameObjectVM
{
public:
	OliveVM(sf::Sprite _sprite, ObjectRect _rect);

	void moveHandler(MoveEventArgs _args);
	~OliveVM() override = default;

	Animation moveAnimation;

};
#include "GVMImplement\OliveVM.hpp"
#endif // OLIVE_VM_H
