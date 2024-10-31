#ifndef RECTANGLE_COLLIDER_H
#define RECTANGLE_COLLIDER_H
#include "Collider.h"

/*An implementation of our collider that uses a rectangle as a base
needs a position, and origin point (center, topleft, etc), and a size(width and height)*/
class RectangleCollider2D :public  Collider
{
public:
	enum ORIGIN{ CENTER, TOPLEFT };
	RectangleCollider2D(Coordinate position, ORIGIN origin, sf::Vector2i size);
	RectangleCollider2D(Coordinate position, ORIGIN origin, sf::Vector2f size);
	RectangleCollider2D();

	void Update(Coordinate new_position)  override;

private:
	ORIGIN m_origin;
	sf::Vector2i m_size;

};
#endif