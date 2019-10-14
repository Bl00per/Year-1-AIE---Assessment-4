#pragma once

#include "Vector2.h"
#include "Renderer2D.h"

class Flock;

class Boid
{

public:
	Boid(aie::Renderer2D* renderer, Vector2& spawn_position, Flock* flock);

	void update(float deltaTime, Vector2& window_dimensions);
	void draw();

	void add_force(Vector2& force);

	Vector2 m_position;
	Vector2 m_velocity;

private:
	float m_circle_radius;
	aie::Renderer2D* m_renderer;

	Flock* m_parent_flock;
};