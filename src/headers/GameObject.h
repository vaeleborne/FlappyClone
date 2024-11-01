#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <iostream>
#include "Collider.h"

//Abstract, to be used as a way to be an observer to our game controller
class GameObject  : public std::enable_shared_from_this<GameObject> 
{
public:
	virtual ~GameObject() = default;
	virtual void OnNotifyEvent(const std::string& event) = 0;
	virtual bool IsColliding(Collider* other) = 0;
	virtual Collider* GetCollider() = 0;
	virtual int GetPositionX() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Reset() = 0;

	//A game object may be a player, need a universal way to check if that is the case
	bool IsPlayer = false;

	//Want a universal way to test if a gameobject has been scored, we may add more types that give score too!
	bool Scored = false;
};
#endif