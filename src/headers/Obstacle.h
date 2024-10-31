#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "GameController.h"
#include "RectangleCollider2D.h"
#include "GameObject.h"
#include "RandomNumberGenerator.h"

class Obstacle : public GameObject
{
    public:

    Obstacle(sf::RenderWindow* window);

    bool _remove = false;

    bool IsColliding(Collider* other) override;
    
    //Avoid using, only gets top collider
    Collider* GetCollider() override {return &m_upper_collider;}


    void Deregister();
    //OVERRIDES

    //Event handling for game controller events
	void OnNotifyEvent(const std::string& ev) override;

    static Obstacle Instantiate(sf::RenderWindow* window);

	void Reset() override;

    int GetPositionX() override {return m_upper_location.GetX();}

    private:
    sf::RectangleShape m_upper_rectangle;
    sf::RectangleShape m_lower_rectangle;
    RectangleCollider2D m_upper_collider;
    RectangleCollider2D m_lower_collider;

    Coordinate m_upper_location;
    Coordinate m_lower_location;

    sf::Vector2f m_velocity;
    
    sf::Vector2i m_horizontal_bounds;
    sf::Vector2i m_vertical_bounds;

    sf::RenderWindow* m_window;

    void Move(sf::RenderWindow* window);

    void Update();
    void Draw();



};

#endif