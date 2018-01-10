
#ifndef LIGHT_SOURCE_M_HPP
#define LIGHT_SOURCE_M_HPP


LightSourceM::LightSourceM(XY _pos, SizeX _width, SizeY _height, XY _lightPos)
	: GameObjectM(LIGHT, _pos, _width, _height), lightPos(_lightPos)
{
}

LightSourceM::~LightSourceM()
{

}


#endif // LIGHT_SOURCE_M_HPP