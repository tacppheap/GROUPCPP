#ifndef GAME_OBJECT_VM_H
#define GAME_OBJECT_VM_H

#include <SFML/Graphics.hpp>
#include "TileField.h"

class GameObjectVM: public std::enable_shared_from_this<GameObjectVM>
{
public:
	GameObjectVM(sf::Sprite& _sprite);
	sf::Sprite& getSprite();
	virtual ~GameObjectVM() = default;
protected:
	sf::Sprite sprite_;

};

#include "GVMImplement\GameObjectVM.hpp"


#endif // GAME_OBJECT_VM_H

