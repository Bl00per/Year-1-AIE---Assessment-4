#pragma once

#include "Renderer2D.h"
#include "Vector2.h"
#include "Matrix3.h"
#include <vector>
#include <ctime>
#include <cstdlib>

class Behaviour;

class Agent
{
public:
	Agent();
	~Agent();

	// Update the agent and its behaviours
	virtual void update(float deltaTime);

	// Draw the agent
	virtual void draw(aie::Renderer2D* renderer);

	// Add a behaviour to the agent
	void AddBehaviour(Behaviour* behaviour);

	Matrix3 m_transform = Matrix3(1.0f);
	Vector2 m_target_position = Vector2(0.0f, 0.0f);
	Vector2 m_screen_center = Vector2(1280, 720) * 0.5;

	enum STEERING_STATE
	{
		NONE,
		SEEK,
		FLEE,
		WANDER
	};

	STEERING_STATE m_current_state;

	void seek(float deltaTime);
	void flee(float deltaTime);
	void wander(float deltaTime);

protected:
	std::vector<Behaviour*> m_BehaviourList;

public:
	aie::Texture* m_texture;

	float m_maxSpeed;
	float m_turn_speed;

	float m_arrival_distance;

	float wander_projection;
	float wander_radius;
	float wander_rotation;

	float wander_min_rand;
	float wander_max_rand;
	int wander_rand;

	float min_wander_time;
	float max_wander_time;
	float current_wander_time;

	Vector2 m_acceleration;
	Vector2 m_velocity;
};

