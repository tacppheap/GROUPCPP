#ifndef PLAYER_VM_HPP
#define PLAYER_VM_HPP



PlayerVM::PlayerVM(sf::Sprite _sprite, ObjectRect _rect) :
											GameObjectVM(_sprite)

{
	sprite_.setOrigin(_rect.width / 2, _rect.height / 2);
	sprite_.setPosition(_rect.pos.x + _rect.width / 2, _rect.pos.y + _rect.height / 2);
	sprite_.setTextureRect(sf::IntRect(0, 0, _rect.width, _rect.height));
	moveAnimation = Animation(_rect.width, _rect.height, defaultFrameCooldown_);
}

void PlayerVM::moveHandler(MoveEventArgs _args)
{

	if (_args.direct == LEFT)
	{
		sprite_.setRotation(-90);
	}

	if (_args.direct == RIGHT)
	{
		sprite_.setRotation(90);

	}
	if (_args.direct == TOP) 
	{
		sprite_.setRotation(0);
	}

	if (_args.direct == BOTTOM)
	{
		sprite_.setRotation(-180);
	}

	PlayerM* player = (PlayerM*)_args.source.get();
	ObjectRect targetObjRect = player->getObjectRect();
	targetObjRect.pos = player->getTargetPos(_args.time, _args.direct);
	sprite_.move(	targetObjRect.pos.x - _args.sourcePos.x,
					targetObjRect.pos.y - _args.sourcePos.y);
	moveAnimation.play(sprite_, _args.time);
}


#endif // PLAYER_VM_HPP