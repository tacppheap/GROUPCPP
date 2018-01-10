#ifndef WALL_M_H
#define WALL_M_H

#include "GameObjectM.h"

class WallM : public GameObjectM
{
public:
	WallM(XY _pos, SizeX _width, SizeY _height);
	~WallM() override;
};

#include "GMImplement\WallM.hpp"

#endif // WALL_M_H
