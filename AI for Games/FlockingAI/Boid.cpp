#include "Boid.h"
#include "Flock.h"
#include "Renderer2D.h"
#include "Agent.h"

Boid::Boid(aie::Renderer2D* renderer, vector_2 & spawn_position, Flock * flock) : m_renderer(renderer), m_parent_flock(flock)
{
	m_circle_radius = 10.0f;

	m_position = spawn_position;

	m_velocity = vector_2(0.0f, 30.0f);

	// If velocity is invalid
	float temp_mag = this->m_velocity.magnitude();
	if (temp_mag <= 0.00001f)
	{
		// Go east
		this->m_velocity = vector_2(m_parent_flock->BOID_SPEED, 0.0f);
	}
	else
	{
		// Set it to the speed it's supposed to be going
		this->m_velocity /= temp_mag;
		this->m_velocity *= m_parent_flock->BOID_SPEED;
	}
}

void Boid::update(float deltaTime, vector_2 & window_dimensions)
{
	std::vector<Boid*> neighbours;
	for (Boid* boid : m_parent_flock->m_boids)
	{
		// dont have a spaz
		if (boid == this)
		{
			continue;
		}
		// Check if it is in the neighbourhood
		if ((boid->m_position - this->m_position).square_magnitude() < m_parent_flock->NEIGHBOUR_RADIUS * m_parent_flock->NEIGHBOUR_RADIUS)
		{
			neighbours.push_back(boid);
		}
	}

	// ~~~Stay in the circle~~~
	// The further it is outside of the circle, the faster it moves towards the circle
	vector_2 world_centre(window_dimensions / 2);
	vector_2 to_centre = world_centre - this->m_position;
	float to_centre_mag = to_centre.magnitude();
	float distance_outside_circle = to_centre_mag - window_dimensions.y / 2;
	if (distance_outside_circle > 0.0f)
	{
		to_centre /= to_centre_mag;
		to_centre *= distance_outside_circle * m_parent_flock->CIRCLE_FORCE_MULT;
		this->add_force(to_centre);
	}

	// ~~~Speration~~~
	// The closer you are to another boid, the faster it moves away
	vector_2 seperation_force;
	for (Boid* neighbour : neighbours)
	{
		vector_2 from_neighbour_to_us = this->m_position - neighbour->m_position;
		from_neighbour_to_us /= from_neighbour_to_us.magnitude();
		from_neighbour_to_us *= m_parent_flock->SEPERATION_FORCE_MAG;
		seperation_force += from_neighbour_to_us;
	}
	this->add_force(seperation_force);

	// ~~~Cohesion~~~ (the action or fact of forming a united whole. [forming a group])
	if (neighbours.size() > 0)
	{
		vector_2 average_neighbour_position;
		for (Boid* neighbour : neighbours)
		{
			average_neighbour_position += neighbour->m_position;
		}
		average_neighbour_position /= neighbours.size();

		vector_2 from_us_to_average = average_neighbour_position - this->m_position;

		from_us_to_average /= from_us_to_average.magnitude();
		from_us_to_average *= m_parent_flock->COHESION_FORCE_MAG;
		this->add_force(from_us_to_average);
	}

	// ~~~Alignment~~~
	// Make sure all neighbours are pointing in same direction
	if (neighbours.size() > 0)
	{
		vector_2 average_neighbour_velocity;
		for (Boid* neighbour : neighbours)
		{
			average_neighbour_velocity += neighbour->m_velocity;
		}
		average_neighbour_velocity /= neighbours.size();

		this->add_force(average_neighbour_velocity *= m_parent_flock->ALIGNMENT_FORCE_MULT);

	}

	// If velocity is invalid
	float temp_mag = this->m_velocity.magnitude();
	if (temp_mag <= 0.00001f)
	{
		// Go east
		this->m_velocity = vector_2(m_parent_flock->BOID_SPEED, 0.0f);
	}
	else
	{
		// Set it to the speed it's supposed to be going
		this->m_velocity /= temp_mag;
		this->m_velocity *= m_parent_flock->BOID_SPEED;
	}
	this->m_position += this->m_velocity * deltaTime;


	vector_2 player_pos(m_parent_flock->m_agent->m_position.x, m_parent_flock->m_agent->m_position.y);

	if (m_parent_flock->m_input->isKeyDown(aie::INPUT_KEY_SPACE))
	{ 
		vector_2 boid_to_player = player_pos - this->m_position;

		float force_maginitude = boid_to_player.magnitude();

		force_maginitude *= 0.1f;
		force_maginitude = m_parent_flock->ATTRACT_MULT / (force_maginitude * force_maginitude);

		boid_to_player /= boid_to_player.magnitude();
		boid_to_player *= force_maginitude;

		this->add_force(boid_to_player);
	}
	else
	{
		vector_2 boid_to_player = player_pos - this->m_position;

		float force_maginitude = boid_to_player.magnitude();

		force_maginitude *= 0.1f;
		force_maginitude = m_parent_flock->REPEL_MULT / (force_maginitude * force_maginitude);

		boid_to_player /= boid_to_player.magnitude();
		boid_to_player *= force_maginitude;

		this->add_force(boid_to_player);
	}
}

void Boid::draw()
{
	m_renderer->setRenderColour(1.0f, 0, 1.0f);
	m_renderer->drawCircle(m_position.x, m_position.y, m_circle_radius);
}

void Boid::add_force(vector_2 & force)
{
	this->m_velocity += force;
}
