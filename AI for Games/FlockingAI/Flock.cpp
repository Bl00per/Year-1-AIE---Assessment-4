#include "Flock.h"
#include "Renderer2D.h"


Flock::Flock()
{
	m_input = aie::Input::getInstance();
}

void Flock::create_boids(aie::Renderer2D* renderer, int amount, vector_2 & window_dimensions)
{
	for (size_t i = 0; i < amount; i++)
	{
		vector_2 new_spawn_position = { float((rand() + 1) % (int)window_dimensions.x), float((rand() + 1) % (int)window_dimensions.y), };

		m_boids.push_back(new Boid(renderer, new_spawn_position, this));
	}
}

void Flock::update(float deltaTime, vector_2 & window_dimensions)
{
	for (Boid* boid : m_boids)
	{
		boid->update(deltaTime, window_dimensions);
	}
}

void Flock::draw()
{
	for (Boid* boid : m_boids)
	{
		boid->draw();
	}
}
