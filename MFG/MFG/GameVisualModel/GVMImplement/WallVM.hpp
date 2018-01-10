#ifndef WALL_VM_HPP
#define WALL_VM_HPP


WallVM::WallVM(sf::Sprite _sprite, ObjectRect _rect) : GameObjectVM(_sprite)
{
	sprite_.setOrigin(_rect.width / 2, _rect.height / 2);
	sprite_.setPosition(_rect.pos.x + _rect.width / 2, _rect.pos.y + _rect.height / 2);
	sprite_.setTextureRect(sf::IntRect(0, 0, _rect.width, _rect.height));
}

#endif // WALL_VM_HPP