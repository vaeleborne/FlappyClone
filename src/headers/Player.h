#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "CircleCollider2D.h"
#include "GameObject.h"
#include "GameController.h"


//Player game object
class Player : public GameObject
{
public:
	Player(Coordinate starting_position, float radius, sf::RenderWindow* window, sf::Color color = sf::Color::Yellow);

	//Updates the player object, updates location, collider, velocity, etc
	void Update();

	//Changes the player's velocity so that it 'jumps', the update function will adjust velocity back to rate of gravity
	void Jump();

	//Draws the player to the render window
	void Draw();



	//OVERRIDES

	int GetPositionX() override {return m_location.GetX();}


    bool IsColliding(Collider* other) override;

	Collider* GetCollider() override {return &m_collider;}

	//Event handling for game controller events
	void OnNotifyEvent(const std::string& ev) override;

	//Reset the position and velocity
	void Reset() override;

	

private:
	//MEMBER VARIABLES
	
	//The rate at which the player falls
	float m_gravity;

	//The rate of change to adjust velocity back to the rate of gravity
	float m_vel_delta;

	CircleCollider2D m_collider;
	sf::CircleShape m_sprite;
	Coordinate m_location;
	sf::Vector2f m_velocity;

	//Reference to our render window
	sf::RenderWindow* m_window;

	//VARIABLES USED FOR RESETTING
	sf::Vector2f m_starting_velocity;
	Coordinate m_starting_location;

	//Moves the player within the window
	void Move(sf::RenderWindow* window);
};

#endif