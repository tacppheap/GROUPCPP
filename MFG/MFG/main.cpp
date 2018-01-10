//#include "GameModel\TileField.h"
//#include "GameModel\GameObjectM.h"
#include "GameModel\WallM.h"
#include "GameModel\PlayerM.h"
#include "GameModel\LevelM.h"
//#include "GameModel\ZombieM.h"
//#include "GameModel\GameObjectM.h"
#include "GameVisualModel\GameObjectVM.h"
#include "GameVisualModel\PlayerVM.h"
#include "GameVisualModel\WallVM.h"
#include "GameVisualModel\LevelVM.h"
#include "GameVisualModel\OliveVM.h"
#include "GameVisualModel\ZombieVM.h"
#include "GameVisualModel\ShadowVM.h"
#include "GameVisual\GameV.h"

//#include "GameModel\MovableObjectM.h"
#include "GameModel\OliveM.h"
#include "GameVisualModel\Animation.h"
#include "GameModel\LightSourceM.h"



void main()


{

	
	std::shared_ptr<GameV> game;
	game = std::make_shared<GameV>();
	game->Run(1366, 768);
	

}

