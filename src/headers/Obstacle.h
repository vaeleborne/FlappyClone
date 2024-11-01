#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "GameController.h"
#include "RectangleCollider2D.h"
#include "GameObject.h"
#include "RandomNumberGenerator.h"

/*An implementation of a gameobject that represents an obstacle, in this case
two rectangular 'pipes' */
class Obstacle : public GameObject
{
public:
    Obstacle(sf::RenderWindow* window);

    //Used to see if we need to deregister as an observer and 'despawn'
    bool _remove = false;

    //Deregister as an observer
    void Deregister();

    //A static function we can use to instantiate a new instance within a render window
    static Obstacle Instantiate(sf::RenderWindow* window);

    //OVERRIDES

    //Collision detection override
     bool IsColliding(Collider* other) override;
    
    //Avoid using, only gets top collider
    Collider* GetCollider() override {return &m_upper_collider;}

    //Event handling for game controller events
	void OnNotifyEvent(const std::string& ev) override;
   
    //Not really used for this implementation
	void Reset() override;

    //Allows us to get our x position
    int GetPositionX() override {return m_upper_location.GetX();}

    private:
    //Entity Variables

    sf::RectangleShape m_upper_rectangle;
    sf::RectangleShape m_lower_rectangle;

    //Collider Variables

    RectangleCollider2D m_upper_collider;
    RectangleCollider2D m_lower_collider;

    //Location Variables

    Coordinate m_upper_location;
    Coordinate m_lower_location;

    //Velocity
    sf::Vector2f m_velocity;
    
    //Render window variables
    sf::RenderWindow* m_window;
    sf::Vector2i m_horizontal_bounds;
    sf::Vector2i m_vertical_bounds;
    
    //Move the object within a window
    void Move();

    //Update our object
    void Update() override;

    //Draw our object
    void Draw() override;
};

#endif