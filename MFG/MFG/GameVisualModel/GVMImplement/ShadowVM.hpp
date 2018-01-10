#ifndef SHADOW_VM_HPP
#define SHADOW_VM_HPP


ShadowVM::ShadowVM(sf::Sprite _sprite) : GameObjectVM(_sprite)
{
}

void ShadowVM::propChangedHandler(std::shared_ptr<ShadowM>& _arg)
{
	sprite_.setPosition(_arg->pos.x , _arg->pos.y );
	sprite_.setScale((pow(_arg->pos.x - _arg->lightPos.x, 2) + pow(_arg->pos.y - _arg->lightPos.y, 2)) / 20000, 1);
	sprite_.setRotation(_arg->angle * 180 / 3.14f);

}

#endif // SHADOW_VM_HPP