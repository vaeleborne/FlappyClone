#include "./headers/RectangleCollider2D.h"

RectangleCollider2D::RectangleCollider2D(Coordinate position, ORIGIN origin, sf::Vector2i size)
{
	m_location = position;
	m_origin = origin;
	m_size = size;

	switch (origin)
	{
	case RectangleCollider2D::CENTER:
		m_bounding_box.left = static_cast<float>(m_location.GetX()) - (size.x / 2.0);
		m_bounding_box.top = static_cast<float> (m_location.GetY()) - (size.y / 2.0);
		break;
	case RectangleCollider2D::TOPLEFT:
		m_bounding_box.left = m_location.GetX();
		m_bounding_box.top = m_location.GetY();
		break;
	default:
		m_bounding_box.left = 0;
		m_bounding_box.top = 0;
		break;
	}

	m_bounding_box.width = size.x;
	m_bounding_box.height = size.y;
}

RectangleCollider2D::RectangleCollider2D(Coordinate position, ORIGIN origin, sf::Vector2f size)
{
	m_location = position;
	m_origin = origin;
	m_size.x = size.x;
	m_size.y = size.y;

	switch (origin)
	{
	case RectangleCollider2D::CENTER:
		m_bounding_box.left = static_cast<float>(m_location.GetX()) - (size.x / 2.0);
		m_bounding_box.top = static_cast<float> (m_location.GetY()) - (size.y / 2.0);
		break;
	case RectangleCollider2D::TOPLEFT:
		m_bounding_box.left = m_location.GetX();
		m_bounding_box.top = m_location.GetY();
		break;
	default:
		m_bounding_box.left = 0;
		m_bounding_box.top = 0;
		break;
	}

	m_bounding_box.width = size.x;
	m_bounding_box.height = size.y;
}

RectangleCollider2D::RectangleCollider2D()
{
	
}

void RectangleCollider2D::Update(Coordinate new_position)
{
	m_location = new_position;

	RectangleCollider2D updated(new_position, m_origin, m_size);

	m_bounding_box = updated.GetBoundingBox();
}
