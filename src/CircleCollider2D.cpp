#include "./headers/CircleCollider2D.h"

CircleCollider2D::CircleCollider2D(Coordinate position, float radius)
{
    m_location = position;
    m_radius = radius;

    m_bounding_box.left = m_location.GetX() - m_radius;
    m_bounding_box.width = 2.0 * m_radius;

    m_bounding_box.top = m_location.GetY() - m_radius;
    m_bounding_box.height = 2.0 * m_radius;
}

CircleCollider2D::CircleCollider2D()
{
    m_location = sf::Vector2i(0, 0);
    m_radius = 0;
}

void CircleCollider2D::Update(Coordinate new_position) 
{
    m_location = new_position;

    CircleCollider2D updated = CircleCollider2D(new_position, m_radius);

    m_bounding_box = updated.GetBoundingBox();
}

