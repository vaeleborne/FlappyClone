#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
#include <vector>
#include <sstream>
#include "GameObject.h"
#include "Player.h"
#include "SoundController.h"

/*A singleton that is our core game controller, is responsible
for making game objects (its observers) update, draw to screen, etc.*/
class GameController
{
public:
	//Enum of possible game states
	enum GAMESTATE {MENU, PLAY, GAME_OVER};

	//Delete copy constructor and assignment operator to prevent copies
	GameController(GameController&) = delete;
	GameController& operator=(const GameController&) = delete;

	//Function to access the single instance
	static GameController& GetInstance();

	//Add an observer game object to the controller
	void AddObserver(const std::shared_ptr<GameObject > &observer);


	//Remove an observer game object from the controller
	void RemoveObserver(const std::shared_ptr<GameObject>& observer);

	//Send an event string to all observers
	void NotifyObservers(const std::string& ev);

	//Resets game objects
	void Reset();

	//Should only be used for player specific events, ie jump
	void NotifyPlayer(const std::string& player_specific_event);

	//Send the 'update' event to all observers
	void UpdateEvent();

	//Send the 'draw' event to all observers
	void DrawEvent();

	//Player class to call this when it 'dies' 
	void PlayerDeadEvent();

	//Sets the render window that our controller will use
	void SetRenderWindow(sf::RenderWindow* window);

	//Displays our title text
	void DisplayTitleText();

	//Displays our game over text
	void DisplayGameOverText();

	//Displays our score text
	void DisplayScoreText();

	//Gets current gamestate
	GAMESTATE GetGameState();

	//Sets the current gamestate
	void SetGameState(GAMESTATE gamestate);

private:
	//Contains our observers that we can send event strings to
	std::vector<std::shared_ptr<GameObject> > m_observers;

	//Conains gameobjects we need to remove, used to allow a cleaning phase and avoid issues of removing them while they are being used
	std::vector<std::shared_ptr<GameObject> > m_pending_removal;

	//Our gamestate
	GAMESTATE m_current_state;

	int m_score = 0; 
	sf::Font m_font;

	//Score Text
	sf::Text m_score_text; 

	//Title Text
	sf::Text m_title_head;
    sf::Text m_title_body;

	//Game Over Text
	sf::Text m_gameover_head;
	sf::Text m_gameover_body;
	sf::Text m_gameover_return;
	
	//Our render window
	sf::RenderWindow* m_window;

	//Private constructor to prevent instantiation
	GameController();

	//Updates our score text based on our current score 
	void UpdateScoreText();
};
#endif