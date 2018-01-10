#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include <vector>
#include <memory>
#include"SFML\Graphics.hpp"
#include "InterfaceObject.h"


class HealthBar: public InterfaceObject
{
public:
	HealthBar(float _xPos, float _yPos):InterfaceObject(), width_(80), height_(20)
	{ 
		backImage_.loadFromFile("GameObjectTextures/wall.png");
		healthImage_.loadFromFile("GameObjectTextures/wall.png");
		back_.loadFromImage(backImage_);
		health_.loadFromImage(healthImage_);
		backSprite.setTexture(back_);
		backSprite.scale(width_ / back_.getSize().x, height_ / back_.getSize().y);
		backSprite.setColor(sf::Color::Black);
		backSprite.setPosition(_xPos, _yPos);
		healthSprite.setTexture(health_);
		healthSprite.scale(0.5*width_ / health_.getSize().x, height_ / health_.getSize().y);

		objects_.push_back(backSprite);
		objects_.push_back(healthSprite);
	}
	void playerHealthChangedHandler(float _procents)
	{
		healthSprite.setScale(_procents*width_ / health_.getSize().x, height_ / health_.getSize().y);

	}
private:
	sf::Sprite healthSprite;
	sf::Sprite backSprite;
	sf::Image backImage_;
	sf::Image healthImage_;
	sf::Texture back_;
	sf::Texture health_;
	float width_;
	float height_;


};


#endif //HEALTH_BAR_H