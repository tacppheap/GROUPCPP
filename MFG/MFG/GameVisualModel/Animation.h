#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

const sf::Time defaultFrameCooldown_ = sf::microseconds(100000);

class Animation
{
public:
	Animation();
	Animation(float _frameWidth, float _frameHeight, sf::Time _frameCooldown, size_t _frameAmount, sf::Texture* _frameList);

	void play(sf::Sprite& _sprite, sf::Time _time);
	void loadTexture(sf::Texture* _texture, size_t _frameAmount);

	sf::Time frameTime;
	sf::Time frameCooldown;
	size_t frameNumInPlay;
	size_t frameAmount;
	float frameWidth;
	float frameHeight;
	sf::Texture* frameList;
};
#include "GVMImplement\Animation.hpp"
#endif // ANIMATION_H

