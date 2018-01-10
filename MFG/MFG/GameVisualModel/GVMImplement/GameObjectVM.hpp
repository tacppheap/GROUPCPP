#ifndef GAME_OBJECT_VM_HPP
#define GAME_OBJECT_VM_HPP


GameObjectVM::GameObjectVM(sf::Sprite& _sprite): sprite_(_sprite)
{
}

sf::Sprite& GameObjectVM::getSprite()
{
	return sprite_;
}




#endif // GAME_OBJECT_VM_HPP

