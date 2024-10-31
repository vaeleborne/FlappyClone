#include "./headers/Collider.h"

bool Collider::IsColliding(Collider* other)
{
	if (m_bounding_box.intersects(other->GetBoundingBox()))
	{
		return true;
	}

	return false;
}

void Collider::SetBoundingBox(sf::FloatRect bounding_box)
{
	m_bounding_box = bounding_box;
}

void Collider::SetLocation(Coordinate location)
{
	m_location = location;
}

sf::FloatRect Collider::GetBoundingBox()
{
	return m_bounding_box;
}