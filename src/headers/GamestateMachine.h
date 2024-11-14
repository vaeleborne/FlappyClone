#ifndef GAMESTATE_MACHINE_H
#define GAMESTATE_MACHINE_H
#include "Player.h"
#include "Obstacle.h"
#include "SoundController.h"

class GamestateMachine
{
    public: 
    //Delete copy constructor and assignment operator to prevent copies
	GamestateMachine(GamestateMachine&) = delete;
	GamestateMachine& operator=(const GamestateMachine&) = delete;

    //Runs the game!
    void RunGame();

    //Function to access the single instance
	static GamestateMachine& GetInstance();

    private: 
    //Private constructor as this is a singleton
    GamestateMachine();         

    bool m_playstate_initialized;

    //VARIABLES FOR TIMING SPAWNING

    sf::Clock m_spawn_clock;
    float m_spawn_time;

    //FUNCTIONS THAT RUN CORE GAME STATES

    //Runs the title menu
    void RunMainMenu(sf::RenderWindow* window);

    //Runs the core game
    void RunPlayState(sf::RenderWindow* window);

    //Runs the game over screen
    void RunGameOver(sf::RenderWindow* window);
};

#endif