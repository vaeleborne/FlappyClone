#include "./headers/Obstacle.h"

Obstacle::Obstacle(sf::RenderWindow* window)
{
    m_window = window;
    m_vertical_bounds = sf::Vector2i(0, m_window->getSize().y);
    m_horizontal_bounds = sf::Vector2i(0, m_window->getSize().x);

    int gap_height = 135;
    int min_height = 50;

    //with a minimum height of 50 per rectangle and a need for 150 pixels of space, owe can calculate max height possible
    int max_height = m_window->getSize().y - gap_height - min_height;

    int upper_rect_height = RandomNumberGenerator::GetInstance().GetIntInRangeInclusive(min_height, max_height);
    int lower_rect_height =  m_window->getSize().y - gap_height - upper_rect_height;


    m_upper_rectangle = sf::RectangleShape(sf::Vector2f(30, upper_rect_height));
    m_lower_rectangle = sf::RectangleShape(sf::Vector2f(30, lower_rect_height));

    m_upper_location = sf::Vector2f(m_horizontal_bounds.y, 0);
    m_lower_location = sf::Vector2f(m_horizontal_bounds.y, m_vertical_bounds.y - m_lower_rectangle.getSize().y);

    m_upper_rectangle.setFillColor(sf::Color::Green);
    m_lower_rectangle.setFillColor(sf::Color::Green);

    m_upper_rectangle.setPosition(m_upper_location.GetX(), m_upper_location.GetY());
    m_lower_rectangle.setPosition(m_lower_location.GetX(), m_lower_location.GetY());


    m_upper_collider = RectangleCollider2D(Coordinate(m_upper_location), RectangleCollider2D::ORIGIN::TOPLEFT, m_upper_rectangle.getSize());
    m_lower_collider  = RectangleCollider2D(Coordinate(m_lower_location), RectangleCollider2D::ORIGIN::TOPLEFT, m_lower_rectangle.getSize());

    m_velocity = sf::Vector2f(-5, 0);
}

bool Obstacle::IsColliding(Collider* other)
{
    bool colliding = false;
    if(m_upper_collider.IsColliding(other))
        colliding = true;
    else if (m_lower_collider.IsColliding(other))
        colliding = true;

    return colliding;
}

void Obstacle::OnNotifyEvent(const std::string& ev)
{
    if (ev == "update")
	{
		this->Update();
	}
	else if (ev == "draw")
	{
		this->Draw();
	}
}

void Obstacle::Move(sf::RenderWindow* window)
{
    float new_x_location = m_upper_location.GetX() + m_velocity.x;
   
    Coordinate newm_upper_location = Coordinate( new_x_location,  m_upper_location.GetY());
    Coordinate newm_lower_location = Coordinate( new_x_location, m_lower_location.GetY());
    

    bool out_bounds[4] = { false, false, false, false };

    //Only need to check x of one rectangle as both move at the same rate!
	if (newm_upper_location.IsInBounds(window, out_bounds))
	{
		m_upper_location = newm_upper_location;
        m_lower_location = newm_lower_location;
	}
    else 
	{
        if(out_bounds[Coordinate::LEFT])
        {
            if(m_upper_location.GetX() < -m_upper_rectangle.getSize().x)
            {
                _remove = true;
            }
            else
            {
                m_upper_location = newm_upper_location;
                m_lower_location = newm_lower_location;
            } 
        }
	}       

    m_upper_collider.Update(m_upper_location);
    m_lower_collider.Update(m_lower_location);

    m_upper_rectangle.setPosition(m_upper_location.GetX(), m_upper_location.GetY());
    m_lower_rectangle.setPosition(m_lower_location.GetX(), m_lower_location.GetY());
}

void Obstacle::Update()
{
    if(!_remove)
    {
        this->Move(m_window);
    }
    else
    { 
        this->Deregister();
    }  
}



void Obstacle::Draw()
{
    m_window->draw(m_upper_rectangle);
    m_window->draw(m_lower_rectangle);   
}

//Not used on this object
void Obstacle::Reset()
{

}

Obstacle Obstacle::Instantiate(sf::RenderWindow* window)
{
    return Obstacle(window);
}

void Obstacle::Deregister() 
{
    GameController::GetInstance().RemoveObserver(shared_from_this());  // Ensure it passes the correct shared_ptr  
}