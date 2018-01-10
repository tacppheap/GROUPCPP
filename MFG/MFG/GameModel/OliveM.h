#ifndef OLIVE_M_H
#define OLIVE_M_H

#include "MovableObjectM.h"
#include "LightSourceM.h"


class OliveM: public MovableObjectM
{
public:
	OliveM(XY _pos, SizeX _width, SizeY _height, float _velocity, Direction _flyDirect);
	~OliveM() override = default;

	std::shared_ptr<LightSourceM> electricLight;

	void tickHandler(sf::Time _time) override;

	const static SizeX oliveDefaultWidth;
	const static SizeY oliveDefaultHeight;
	const static SizeX oliveDefaultElectricLightWidth;
	const static SizeY oliveDefaultElectricLightHeight;


	Direction flyDirect_;



};

#include "GMImplement\OliveM.hpp"
#endif // OLIVE_M_H