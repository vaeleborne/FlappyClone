#ifndef CIRCLE_COLLIDER_2D_H
#define CIRCLE_COLLIDER_2D_H
#include "Collider.h"

/*An implementation of our collider that uses a circle as a base
only needs a postion and radius to create. Note the collider is a square!*/
class CircleCollider2D : public Collider
{
public:
	CircleCollider2D(Coordinate position, float radius);
	CircleCollider2D();
	void Update(Coordinate new_position)  override;
private:
	float m_radius;	
};
#endif