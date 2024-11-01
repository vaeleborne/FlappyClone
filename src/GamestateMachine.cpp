#include "./headers/GamestateMachine.h"

GamestateMachine::GamestateMachine()
{
	//ADJUST TO SPAWN OBSTACLES AT A DIFFERENT RATE (in seconds)
    m_spawn_time = 2.5f;
}

GamestateMachine& GamestateMachine::GetInstance()
{
    static GamestateMachine instance;
    return instance;
}

void GamestateMachine::RunGame()
{
    sf::RenderWindow window(sf::VideoMode(800, 400), "Flappy Clone");
	window.setFramerateLimit(30);
	sf::Event ev;


	auto player = std::make_shared<Player>(Coordinate(50, 190), 10.f, &window);

	GameController& game_controller = GameController::GetInstance();
	game_controller.SetRenderWindow(&window);
	game_controller.AddObserver(player);
	game_controller.SetGameState(GameController::GAMESTATE::MENU);
	

	while(window.isOpen())
	{
		switch (game_controller.GetGameState())
		{
		case GameController::GAMESTATE::MENU:
			RunMainMenu(&window);
			break;
		case GameController::GAMESTATE::PLAY:
			RunPlayState(&window);
			break;

		case GameController::GAMESTATE::GAME_OVER:
			RunGameOver(&window);
			game_controller.Reset();
			game_controller.UpdateEvent();
			break;
		
		default:
			break;
		}
	}
}

void GamestateMachine::RunMainMenu(sf::RenderWindow* window)
{
    sf::Event ev;
	GameController& game_controller = GameController::GetInstance();

	while(window->isOpen())
	{
		while(window->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed || ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				window->close();
			}
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
			{
				game_controller.SetGameState(GameController::GAMESTATE::PLAY);
				return;
			}
		}
		window->clear(sf::Color::Blue);
		game_controller.DrawEvent();
		game_controller.DisplayTitleText();
		window->display();
	}
}
void GamestateMachine::RunPlayState(sf::RenderWindow* window)
{
    sf::Event ev;

	GameController& game_controller = GameController::GetInstance();

	//game_controller.AddObserver(std::make_shared<Obstacle>(Obstacle::Instantiate(window)));

	bool should_jump = false;
	bool has_jumped = false;

	while (window->isOpen())
	{
        //EVENT POLLING
		while (window->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed || ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				window->close();
			}
			else if (ev.type == sf::Event::KeyPressed)
			{
				if(ev.key.code == sf::Keyboard::Space)
				{
					if(!should_jump)
					{
						should_jump = true;
					}
				}
				
			}
			else if (ev.type == sf::Event::KeyReleased)
			{
				if(ev.key.code == sf::Keyboard::Space)
				{
					if(should_jump)
					{
						should_jump = false;
						has_jumped = false;
					}
				}
				
			}
		}


        //UPDATING
		if(should_jump && !has_jumped)
		{
			game_controller.NotifyPlayer("jump");
			has_jumped = true;
		}
		
		//UPDATE PHASE
		game_controller.UpdateEvent();

		if(game_controller.GetGameState() != GameController::GAMESTATE::PLAY)
		{
			return;
		}

        //Instantiating
        if(m_spawn_clock.getElapsedTime().asSeconds() > m_spawn_time)
        {
            game_controller.AddObserver(std::make_shared<Obstacle>(Obstacle::Instantiate(window)));
            m_spawn_clock.restart();
        }

		window->clear(sf::Color::Blue);
		
		game_controller.DrawEvent();

		window->display();
	}
}
void GamestateMachine::RunGameOver(sf::RenderWindow* window)
{
    sf::Event ev;
	while (window->isOpen())
	{

		while(window->pollEvent(ev))
		{
			if(ev.type == sf::Event::Closed || ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				window->close(); 
			}
			if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::P)
			{
				GameController::GetInstance().SetGameState(GameController::GAMESTATE::MENU);
				return;
			}
		}
		window->clear();
		GameController::GetInstance().DisplayGameOverText();
		window->display();
	}
}