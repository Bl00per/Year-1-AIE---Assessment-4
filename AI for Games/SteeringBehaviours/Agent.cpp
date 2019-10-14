#include "Agent.h"
#include "Texture.h"
#include "Behaviour.h"

Agent::Agent()
{
	m_texture = new aie::Texture("./bin/textures/playerArrow.png");

	m_transform[2] = Vector3(m_screen_center.x, m_screen_center.y, 1);
	m_current_state = SEEK;
	m_target_position = m_screen_center * 0.5f; // Half way to 0.0f
	m_maxSpeed = 50.0f;
	m_turn_speed = 0.5f;
	m_arrival_distance = 50.0f;
	wander_projection = 100.0f;
	wander_radius = 50.0f;
	wander_rotation = 0.0f;
	wander_min_rand = -0.1f;
	wander_max_rand = 0.1f;
	wander_rand = 200;
	max_wander_time = 2.0f;
	min_wander_time = 10.0f;
	current_wander_time = 0.0f;

	srand(time(nullptr));
}


Agent::~Agent()
{
}

void Agent::AddBehaviour(Behaviour* behaviour)
{
	m_BehaviourList.push_back(behaviour);
}

void Agent::update(float deltaTime)
{
	if (m_current_state == NONE)
	{
		m_current_state = WANDER;
	}

	switch (m_current_state)
	{
	case SEEK:
	{
		seek(deltaTime);
		break;
	}
	case FLEE:
	{
		flee(deltaTime);
		break;
	}
	case WANDER:
	{
		wander(deltaTime);
		break;
	}
	}
}

void Agent::draw(aie::Renderer2D* renderer)
{
	renderer->drawSpriteTransformed3x3(m_texture, m_transform, 30.0f, 30.0f);
}

void Agent::seek(float deltaTime)
{
	Vector2 target_direction = m_target_position - Vector2(m_transform[2].x, m_transform[2].y);
	float distance = target_direction.magnitude();
	target_direction.normalise();

	// Rotate towards - Two dot prods required
	float dot_forward = Vector2(m_transform[1].x, m_transform[1].y).dot(target_direction);
	float dot_right = Vector2(m_transform[0].x, m_transform[0].y).dot(target_direction);

	if (dot_forward < 0.995f) // Ahead
	{
		if (dot_right > 0) // Turn right
		{
			Matrix3 rotateMatrix = Matrix3(1.0f);
			rotateMatrix.setRotateZ(-m_turn_speed * deltaTime);
			m_transform = m_transform * rotateMatrix;
		}
		else // turn left
		{
			Matrix3 rotateMatrix = Matrix3(1.0f);
			rotateMatrix.setRotateZ(m_turn_speed * deltaTime);
			m_transform = m_transform * rotateMatrix;
		}
	}

	// Move towards
	m_transform[2] += m_transform[1] * m_maxSpeed * dot_forward * deltaTime;


	// Check if arrived
	if (distance < m_arrival_distance)
	{
		// If arrived - Wander
		// ENTERING WANDER STATE
		m_current_state = WANDER;
		current_wander_time = (rand() % int(max_wander_time - min_wander_time)) + min_wander_time;
	}

	// If arrived - wander
}

void Agent::flee(float deltaTime)
{
	Vector2 target_direction = m_target_position - Vector2(m_transform[2].x, m_transform[2].y);
	float distance = target_direction.magnitude();
	target_direction.normalise();

	// Rotate towards - Two dot prods required
	float dot_forward = Vector2(m_transform[1].x, m_transform[1].y).dot(target_direction);
	float dot_right = Vector2(m_transform[0].x, m_transform[0].y).dot(target_direction);

	if (dot_forward > -0.995f) // Negatory heading
	{
		if (dot_right > 0) // Turn right
		{
			Matrix3 rotate_matrix = Matrix3(1.0f);
			rotate_matrix.setRotateZ(m_turn_speed * deltaTime); // Negatory speed
			m_transform = m_transform * rotate_matrix;
		}
		else // turn left
		{
			Matrix3 rotate_matrix = Matrix3(1.0f);
			rotate_matrix.setRotateZ(-m_turn_speed * deltaTime); // Negatory speed
			m_transform = m_transform * rotate_matrix;
		}
	}

	// Move towards
	m_transform[2] += m_transform[1] * m_maxSpeed * -dot_forward * deltaTime; // Negatory forward

	// Bounds check
	if (m_transform[2].x < 0 || m_transform[2].x > 1280 ||
		m_transform[2].y < 0 || m_transform[2].y > 720)
	{
		// ENTERING SEEK STATE
		m_current_state = SEEK;
		m_target_position = m_screen_center;
	}
}

void Agent::wander(float deltaTime)
{
	current_wander_time -= deltaTime;
	if (current_wander_time <= 0)
	{
		// ENTERING FLEE STATE
		m_current_state = FLEE;
		return;
	}

	Matrix3 vector_rotator = Matrix3(1);

	int this_rand = rand();
	this_rand %= 200; // 0 - 199
	this_rand -= 100; // -100 - 99
	float rand_result = this_rand / 1000.0f; // -0.1 - 0.099

	wander_rotation += rand_result;

	vector_rotator.setRotateZ(wander_rotation);
	Vector3 wander_vector = vector_rotator * Vector3(m_transform[1].x, m_transform[1].y, 0);
	wander_vector = wander_vector * wander_radius;

	// Adjust the wander point
	m_target_position =
		// Objects position
		Vector2(m_transform[2].x, m_transform[2].y) +
		// Objects forward * distance to wander circle origin
		Vector2(m_transform[1].x, m_transform[1].y) * wander_projection +
		// Vector of length radius with wander rotation applied
		Vector2(wander_vector.x, wander_vector.y);


	// Seek to wander
	seek(deltaTime);
}
