#ifndef OLIVE_M_HPP
#define OLIVE_M_HPP

const SizeX OliveM::oliveDefaultWidth = 37;
const SizeY OliveM::oliveDefaultHeight = 35;

const SizeX OliveM::oliveDefaultElectricLightWidth = 200;
const SizeY OliveM::oliveDefaultElectricLightHeight = 200;






OliveM::OliveM(XY _pos, SizeX _width, SizeY _height, float _velocity, Direction _flyDirect): 
																	MovableObjectM(OLIVE, _pos, _width, _height, _velocity), 
																	flyDirect_(_flyDirect)
{
	electricLight = std::make_shared<LightSourceM>	(
														XY(	_pos.x - (oliveDefaultElectricLightWidth - objRect_.width) / 2,
															_pos.y - (oliveDefaultElectricLightHeight - objRect_.height) / 2),
														oliveDefaultElectricLightWidth,
														oliveDefaultElectricLightHeight,
														XY(_pos.x + objRect_.width / 2, _pos.y + objRect_.height / 2)
													);
}

void OliveM::tickHandler(sf::Time _time)
{
	moveRequest(_time, flyDirect_);
}

#endif // OLIVE_M_HPP


