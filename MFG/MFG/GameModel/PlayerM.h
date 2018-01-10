#ifndef PLAYER_M_H
#define PLAYER_M_H

#include "MovableObjectM.h"
#include "OliveM.h"

typedef float ProcentOfMaxHealth;
typedef float HealthPoints;

class PlayerM : public MovableObjectM
{
public:
	PlayerM(XY _pos, SizeX _width, SizeY _height, float _velocity);
	~PlayerM() override;
	void shoot( std::shared_ptr<OliveM>& _olive);

	Direction getViewDirect();
	float getMaxHealth();
	float getHealth();
	sf::Time getCurrentShootCooldown();

	std::shared_ptr<LightSourceM> electricLight;

	void setHealth(HealthPoints _health);

	Event<std::shared_ptr<OliveM>&> shootEvent;
	Event<ProcentOfMaxHealth> healthChangedEvent;
	Event<EmptyArg> youDiedEvent;
	Event<StrongObjectPtr&> shadowCheckEvent;

	void tickHandler(sf::Time _time) override;

	Direction viewDirect_;

	const static SizeX defaultElectricLightWidth;
	const static SizeY defaultElectricLightHeight;

private:
	HealthPoints maxHealth_;
	HealthPoints currentHealth_;;
	sf::Time maxShootCooldown;
	sf::Time currentShootCooldown;

};
#include "GMImplement\PlayerM.hpp"

#endif // PLAYER_M_H