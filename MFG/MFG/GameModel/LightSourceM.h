#ifndef LIGHT_SOURCE_M_H
#define LIGHT_SOURCE_M_H

#include "GameObjectM.h"

class LightSourceM : public GameObjectM
{
public:
	LightSourceM(XY _pos, SizeX _width, SizeY _height, XY _lightPos);
	~LightSourceM() override;

	float radius;
	XY lightPos;
};

#include "GMImplement\LightSourceM.hpp"

#endif // LIGHT_SOURCE_M_H