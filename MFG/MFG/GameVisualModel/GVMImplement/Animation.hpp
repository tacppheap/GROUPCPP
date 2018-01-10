#ifndef ANIMATION_HPP
#define ANIMATION_HPP


Animation::Animation(float _frameWidth, float _frameHeight, sf::Time _frameCooldown, size_t _frameAmount = 0, sf::Texture* _frameList = nullptr):
	frameCooldown(_frameCooldown),
	frameHeight(_frameHeight),
	frameWidth(_frameWidth),
	frameAmount(_frameAmount),
	frameNumInPlay(0),
	frameList(_frameList),
	frameTime(sf::Time::Zero)
{
	if (_frameList != nullptr)
	{
		frameAmount = (*_frameList).getSize().x / _frameWidth;
	}
}

Animation::Animation():		frameCooldown(sf::Time::Zero),
							frameHeight(0),
							frameWidth(0),
							frameNumInPlay(0),
							frameList(0),
							frameTime(sf::Time::Zero),
							frameAmount(0)
{
}

void  Animation::loadTexture(sf::Texture* _texture, size_t _frameAmount)
{
	frameList = _texture;
	frameAmount = _frameAmount;
}

void Animation::play(sf::Sprite& _sprite, sf::Time _time)
{
	if (frameList == nullptr)
	{
		return;
	}

	frameTime += _time;
	if (frameTime >= frameCooldown)
	{
		frameTime = sf::Time::Zero;
		++frameNumInPlay;

		if (frameNumInPlay >= frameAmount)
		{
			frameNumInPlay = 0;
		}
	}

	_sprite.setTexture(*frameList);
	_sprite.setTextureRect(sf::IntRect(	frameNumInPlay * frameWidth,
										0,
										frameWidth,
										frameHeight));
}

#endif // ANIMATION_HPP
