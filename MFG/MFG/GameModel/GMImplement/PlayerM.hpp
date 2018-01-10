#ifndef PLAYER_M_HPP
#define PLAYER_M_HPP

const SizeX PlayerM::defaultElectricLightWidth = 200;
const SizeY PlayerM::defaultElectricLightHeight = 200;

PlayerM::PlayerM(XY _pos, SizeX _width, SizeY _height, float _velocity):
																	MovableObjectM(PLAYER, _pos, _width, _height, _velocity),
																	viewDirect_(RIGHT),
																	maxShootCooldown(sf::milliseconds(500)),
																	currentShootCooldown(sf::Time::Zero),
																	currentHealth_(50),
																	maxHealth_(100)
{
		electricLight = std::make_shared<LightSourceM>(
		XY(_pos.x - (defaultElectricLightWidth - objRect_.width) / 2,
			_pos.y - (defaultElectricLightHeight - objRect_.height) / 2),
		defaultElectricLightWidth,
		defaultElectricLightHeight,
		XY(_pos.x + objRect_.width / 2, _pos.y + objRect_.height / 2)
		);
}

void PlayerM::setHealth(HealthPoints _health)
{
	if (_health <= 0)
	{
		youDiedEvent.invoke(EmptyArg());
		return;
	}

	currentHealth_ = _health;

	if (_health > maxHealth_)
	{
		currentHealth_ = maxHealth_;
	}

	healthChangedEvent.invoke(currentHealth_ / maxHealth_);
}

HealthPoints  PlayerM::getMaxHealth()
{
	return maxHealth_;
}

HealthPoints  PlayerM::getHealth()
{
	return currentHealth_;
}


PlayerM::~PlayerM() 
{
}

Direction PlayerM::getViewDirect()
{
	return viewDirect_;
}

void PlayerM::tickHandler(sf::Time _time)
{

	if (currentShootCooldown > sf::Time::Zero)
	{
		currentShootCooldown -= _time;
	}

	shadowCheckEvent.invoke(shared_from_this());
}

sf::Time PlayerM::getCurrentShootCooldown()
{
	return currentShootCooldown;
}

void PlayerM::shoot(std::shared_ptr<OliveM>& _olive)
{
	if (currentShootCooldown <= sf::Time::Zero)
	{
		shootEvent.invoke( _olive);
		currentShootCooldown = maxShootCooldown;
	}

}

#endif // PLAYER_M_HPP
