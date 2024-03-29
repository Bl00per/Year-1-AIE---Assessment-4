#pragma once

#include "Renderer2D.h"
#include "Vector2.h"
#include <vector>

class Behaviour;

class Agent
{
public:
	Agent(float x, float y);
	~Agent();

	// Update the agent and its behaviours
	virtual void update(float deltaTime);

	// Draw the agent
	virtual void draw(aie::Renderer2D* renderer);

	// Add a behaviour to the agent
	void AddBehaviour(Behaviour* behaviour);

protected:
	std::vector<Behaviour*> m_BehaviourList;

public:
	float m_maxSpeed;

	Vector2 m_acceleration;
	Vector2 m_position;
	Vector2 m_velocity;
};

