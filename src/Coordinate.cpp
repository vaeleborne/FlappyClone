#include "./headers/Coordinate.h"

Coordinate::Coordinate(sf::Vector2i location)
{
	m_location = location;
}

Coordinate::Coordinate(int x, int y)
{
	m_location = sf::Vector2i(x, y);
}

int Coordinate::GetX()
{
	return m_location.x;
}

int Coordinate::GetY()
{
	return m_location.y;
}

bool Coordinate::IsInBounds(sf::RenderWindow* window, bool out_of_bounds[4])
{
	bool in_bounds = true;
	sf::Vector2u window_bounds = window->getSize();

	//Checking X boundaries
	if (m_location.x < 0)
	{
		in_bounds = false;
		out_of_bounds[LEFT] = true;
	}
	else if (m_location.x > window_bounds.x)
	{
		in_bounds = false;
		out_of_bounds[RIGHT] = true;
	}

	//Checking Y boundaries
	if (m_location.y < 0)
	{
		in_bounds = false;
		out_of_bounds[TOP] = true;
	}
	else if (m_location.y > window_bounds.y)
	{
		in_bounds = false;
		out_of_bounds[BOTTOM] = true;
	}

	return in_bounds;
}