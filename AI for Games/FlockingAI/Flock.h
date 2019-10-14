#pragma once
#include "Boid.h"
#include "Input.h"
#include "Agent.h"
#include <vector>

class Flock
{
public:
	Flock();

	void create_boids(aie::Renderer2D* renderer, int amount, Vector2& window_dimensions);

	void update(float deltaTime, Vector2& window_dimensions);
	void draw();

	std::vector<Boid*> m_boids;

	float NEIGHBOUR_RADIUS = 25.0f;
	float BOID_SPEED = 100.0f;
	float SEPERATION_FORCE_MAG = 20.0f;
	float COHESION_FORCE_MAG = 20.0f;
	float CIRCLE_FORCE_MULT = 10.0f;
	float ALIGNMENT_FORCE_MULT = 7.0f;
	float ATTRACT_MULT = 20.0f * 1000.0f;
	float REPEL_MULT = -(20.0f * 1000.0f);

	aie::Input* m_input;
	Agent* m_agent;
};

