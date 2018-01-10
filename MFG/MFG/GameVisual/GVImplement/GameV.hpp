#ifndef GAME_V_HPP
#define GAME_V_HPP

GameV::GameV() : isPlay_(true), message_("YOU DIED")
{
	level_ = std::make_shared<LevelVM>();
	level_->loadModel("tilesets/MFM/MSM.tmx");
	interface_ = std::make_shared<Interface>();
	std::shared_ptr<HealthBar> healthBar = std::make_shared<HealthBar>(0,0);
	interface_->AddObject(healthBar);
	level_->levelM_->mainPlayer_.lock()->healthChangedEvent.Add(healthBar, &HealthBar::playerHealthChangedHandler);
}

void GameV::playerDiedHandler(EmptyArg _arg)
{
	isPlay_ = false;
}

void GameV::Run(int _width, int _height)

{
	level_->playerDiedEvent.Add(shared_from_this(), &GameV::playerDiedHandler);

	sf::RenderWindow window(sf::VideoMode(_width, _height), "MFG", sf::Style::Fullscreen);
	sf::View view;
	int viewH = 300;
	int viewW = viewH * _width / _height;
	int halfViewH = viewH / 2;
	int halfViewW = viewW / 2;
	int mapW = level_->levelM_->tileField_->getWidth() * level_->levelM_->tileField_->getTileWidth();
	int mapH = level_->levelM_->tileField_->getHeight() * level_->levelM_->tileField_->getTileHeight();

	view.setCenter(halfViewW, halfViewH);
	view.reset(sf::FloatRect(0, 0, viewW, viewH));
	sf::Clock clock;
	sf::Time time;

	sf::Texture backGround;
	backGround.loadFromFile("GameObjectTextures/back.png");
	sf::Sprite back;
	back.setTexture(backGround);
	while (window.isOpen() && isPlay_)
	{
		time = clock.restart();
		level_->updateModel(time);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		X x = level_->levelM_->mainPlayer_.lock()->getObjectRect().pos.x;
		Y y = level_->levelM_->mainPlayer_.lock()->getObjectRect().pos.y;

		if (x + halfViewW >= mapW)
		{
			x = mapW - halfViewW;
		}

		if (x - halfViewW < 0)
		{
			x = halfViewW;
		}

		if (y + halfViewH >= mapH)
		{
			y = mapH - halfViewH;
		}

		if (y - halfViewH < 0)
		{
			y = halfViewH;
		}

		X dx = x - view.getCenter().x;
		Y dy = y - view.getCenter().y;

		view.move(dx, dy);

		window.clear(sf::Color::White);
		window.draw(back);


		
		for (auto it = level_->shadowVMStore_.begin(); it != level_->shadowVMStore_.end(); ++it)
		{
			window.draw(it->second->getSprite());
		}

		for (auto it = level_->gameObjectVMStore_.begin(); it != level_->gameObjectVMStore_.end(); ++it)
		{
			window.draw(it->second->getSprite());
		}

		for (auto it = interface_->objectStore_.begin(); it != interface_->objectStore_.end(); ++it)
		{
			for (auto it1= (*it)->objects_.begin(); it1 != (*it)->objects_.end(); it1++)
			{
				window.draw(*it1);
			}
		}

		for (auto it = interface_->objectStore_.begin(); it != interface_->objectStore_.end(); ++it)
		{
			for (auto it1 = (*it)->objects_.begin(); it1 != (*it)->objects_.end(); it1++)
			{
				(*it1).get().setPosition((*it1).get().getPosition().x + dx, (*it1).get().getPosition().y + dy);
			}
		}
		window.setView(view);
		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			level_->levelM_->shootMainPlayer();

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			level_->levelM_->moveMainPlayer(LEFT, clock.getElapsedTime());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			level_->levelM_->moveMainPlayer(RIGHT, clock.getElapsedTime());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			level_->levelM_->moveMainPlayer(TOP, clock.getElapsedTime());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			level_->levelM_->moveMainPlayer(BOTTOM, clock.getElapsedTime());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Font was not found";
	}
	sf::Text text;
	text.setFont(font);
	text.setString("YOU DIED");

	text.setPosition(view.getCenter().x , view.getCenter().y);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	if (!isPlay_)
	{
		while (window.isOpen())
		{
			window.draw(text);
			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{				
				window.close();
			}
		}
	}
}



#endif // GAME_V_HPP