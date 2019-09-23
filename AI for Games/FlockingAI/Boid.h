#pragma once

#include "vector_2.h"
#include "Renderer2D.h"

class Flock;

class Boid
{

public:
	Boid(aie::Renderer2D* renderer, vector_2& spawn_position, Flock* flock);

	void update(float deltaTime, vector_2& window_dimensions);
	void draw();

	void add_force(vector_2& force);

	vector_2 m_position;
	vector_2 m_velocity;

private:
	float m_circle_radius;
	aie::Renderer2D* m_renderer;

	Flock* m_parent_flock;
};