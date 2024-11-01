#ifndef COLLIDER_H
#define COLLIDER_H
#include "Coordinate.h"

/*Base class for our custom colliders. All colliders have a 
location and bounding box as well as a method to update its position and check if it 
is colliding with another collider*/
class Collider
{
public:
	//Check to see if this collider is colliding with another
	bool IsColliding(Collider* other);

	//Virtual function, children will implement a way to update their position and bounding box
	virtual void Update(Coordinate new_position) = 0;

	virtual ~Collider() = default;

	//Gets our bounding box
	sf::FloatRect GetBoundingBox();

	//SETTERS
	void SetLocation(Coordinate location);
	void SetBoundingBox(sf::FloatRect bounding_box);

protected:
	Coordinate m_location;
	sf::FloatRect m_bounding_box;
};

#endif