#include "./headers/Player.h"

//Constructor
Player::Player(Coordinate starting_position, float radius, sf::RenderWindow* window, sf::Color color)
{
	m_location = starting_position;
	m_starting_location = m_location;
	m_sprite = sf::CircleShape(radius);
	IsPlayer = true;
	m_collider = CircleCollider2D(m_location, radius);
	m_sprite.setFillColor(color);
	m_sprite.setPosition(m_location.GetX(), m_location.GetY());
	m_gravity = 8.f;
	m_vel_delta = 2.f;
	m_velocity = sf::Vector2f(0, m_gravity);
	m_starting_velocity = m_velocity;
	m_window = window;
}

void Player::Jump()
{
	m_velocity.y = -2.f * m_gravity;
}

void Player::Draw()
{
	m_window->draw(this->m_sprite);
}

void Player::Update()
{
	this->Move(m_window);  
}

void Player::Reset()
{
	m_location = m_starting_location;
	m_velocity = m_starting_velocity;
}

void Player::OnNotifyEvent(const std::string& ev)
{
	if (ev == "update")
	{
		this->Update();
	}
	else if (ev == "draw")
	{
		this->Draw();
	}
	else if (ev == "jump")
	{
		this->Jump();
	}
}



void Player::Move(sf::RenderWindow* window)
{
	Coordinate new_location = Coordinate( m_location.GetX() + m_velocity.x, m_location.GetY() + m_velocity.y);

	if(m_velocity.y != m_gravity)
	{
		m_velocity.y += m_vel_delta;
		if(m_velocity.y > m_gravity)
		{
			m_velocity.y = m_gravity;
		}
	}

	bool out_bounds[4] = { false, false, false, false };

	if (new_location.IsInBounds(window, out_bounds))
	{
		m_location = new_location;
	}
	else
	{
		if (out_bounds[Coordinate::TOP])
		{
			m_location.SetY(m_sprite.getRadius());

			//TODO decide if we want this line, it adds more of a 'bounce' leaning yes
			m_velocity.y *= -1;
		}
		else if (out_bounds[Coordinate::BOTTOM])
		{
			GameController::GetInstance().PlayerDeadEvent();
		}
	}

	m_collider.Update(m_location);
	m_sprite.setPosition(m_location.GetX(), m_location.GetY());
}


bool Player::IsColliding(Collider* other)
{
	return m_collider.IsColliding(other);
}