#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
#include <vector>
#include <sstream>
#include "GameObject.h"
#include "Player.h"

/*A singleton that is our core game controller, is responsible
for making game objects (its observers) update, draw to screen, etc.*/
class GameController
{
public:
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

	void SetRenderWindow(sf::RenderWindow* window);

	void DisplayTitleText();

	void DisplayGameOverText();



	//Gets current gamestate
	GAMESTATE GetGameState();

	//Sets the current gamestate
	void SetGameState(GAMESTATE gamestate);


private:
	std::vector<std::shared_ptr<GameObject> > m_observers;
	std::vector<std::shared_ptr<GameObject> > m_pending_removal;

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
	

	sf::RenderWindow* m_window;

	//Private constructor to prevent instantiation
	GameController();

	void UpdateScoreText(int score);
};
#endif