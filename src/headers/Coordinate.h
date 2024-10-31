#ifndef COORDINATE_H
#define COORDINATE_H
#include <SFML/Graphics.hpp>

/*A simple coordinate object, it has an x,y location. It also contains a function
to check if that location is within the given bounds of a window and sets a boolean array
appropriately if out of bounds. IE if out of bounds left bounds[LEFT] is set to true*/
class Coordinate
{
public:
	enum BOUNDS {LEFT, RIGHT, TOP, BOTTOM};

	//Checks to see if current coordinate is within window boundaries, sets a boolean array for out of bounds appropriately
	bool IsInBounds(sf::RenderWindow* window, bool out_of_bounds[4]);

	//CONSTRUCTORS
	Coordinate(sf::Vector2i location);
	Coordinate(sf::Vector2f location) {m_location.x = location.x; m_location.y = location.y;}
	Coordinate(int x, int y);
	Coordinate() { m_location = sf::Vector2i(0, 0); }

	//GETTERS
	int GetX();
	int GetY();

	//SETTERS
	void SetX(int x) { m_location.x = x; }
	void SetY(int y) { m_location.y = y; }



private:
	sf::Vector2i m_location;
};
#endif