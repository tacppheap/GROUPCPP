#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <memory>
#include "InterfaceObject.h"

class Interface
{
public:
	std::vector<std::shared_ptr<InterfaceObject>> objectStore_;
	void AddObject(std::shared_ptr<InterfaceObject> _object)
	{
		objectStore_.push_back(_object);
	}
};

#endif //INTERFACE_H
