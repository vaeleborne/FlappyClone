#include "./headers/GamestateMachine.h"

/* This program serves as my take of a flappy bird game clone for macos. 

	I wanted to come up with a project to show my skill and knowledge of several 
	design patterns as well as C++ and SFML. I utilize a singleton as the core game controller,
	I make use of the observer pattern to easily update game objects. I use a state machine for controlling 
	flow of the game between menus and modes.

	Started on: 10/27/24


	AUTHOR: Dylan Morgan


	UPDATED on: 11/14/24

	FUTURE GOALS:
		Use a decorator to have file input and output (with encryption)
		Save and load high score from a file

		Rework player entity to be a sprite! (make a ciruclar sprite design)
		Rework obstacle shapes to be a sprite (will need two portions, one for the top/bottom and one that can be repeated 
			due to the varying size of the obstacle)

		Finally: Look for optimizations
*/

int main()
{
	GamestateMachine::GetInstance().RunGame();	
}
