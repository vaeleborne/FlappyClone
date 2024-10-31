#ifndef GAMESTATE_MACHINE_H
#define GAMESTATE_MACHINE_H
#include "Player.h"
#include "Obstacle.h"

class GamestateMachine
{
    public: 
    //Delete copy constructor and assignment operator to prevent copies
	GamestateMachine(GamestateMachine&) = delete;
	GamestateMachine& operator=(const GamestateMachine&) = delete;

    void RunGame();

    //Function to access the single instance
	static GamestateMachine& GetInstance();

    private: 
    GamestateMachine();
    sf::Clock m_spawn_clock;
    float m_spawn_time;

    void RunMainMenu(sf::RenderWindow* window);
    void RunPlayState(sf::RenderWindow* window);
    void RunGameOver(sf::RenderWindow* window);
};

#endif