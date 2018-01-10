#ifndef GAME_V_H
#define GAME_V_H

#include "TileField.h"
#include "GameVisualModel\LevelVM.h"
#include"Interface.h"
#include"HealthBar.h"
#include <string>
#include <iostream>
#include "HSL.h"

class GameV: public std::enable_shared_from_this<GameV>
{
private:
	std::shared_ptr<LevelVM> level_;
	std::shared_ptr<Interface> interface_;
	std::string message_;
	bool isPlay_;

public:
	GameV();
	void Run(int _width, int _height);
	void playerDiedHandler(EmptyArg _arg);
};

#include "GVImplement/GameV.hpp"

#endif // GAME_V_H
