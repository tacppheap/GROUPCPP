#ifndef SHADOW_VM_H
#define SHADOW_VM_H

#include "GameObjectVM.h" 

class ShadowVM : public GameObjectVM
{
public:
	ShadowVM(sf::Sprite _sprite);
	void propChangedHandler(std::shared_ptr<ShadowM>& _arg);
	~ShadowVM() override = default;

};
#include "GVMImplement\ShadowVM.hpp"

#endif // SHADOW_VM_H
