#ifndef INTERFACE_OBJECT_H
#define INTERFACE_OBJECT_H

#include <vector>
#include <memory>
#include"SFML\Graphics.hpp"


class InterfaceObject
{
public:
	std::vector<std::reference_wrapper<sf::Sprite>> objects_ ;	
};


#endif //INTERFACE_OBJECT_H

