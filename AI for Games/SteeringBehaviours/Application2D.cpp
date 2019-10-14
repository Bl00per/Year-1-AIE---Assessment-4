#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./bin/font/consolas.ttf", 32);

	m_window_dimensions = { float(getWindowWidth()), float(getWindowHeight()) };

	m_agent = new Agent();

	m_timer = 0;

	return true;
}

void Application2D::shutdown() {

	delete m_font;
	m_font = nullptr;
	delete m_2dRenderer;
	m_2dRenderer = nullptr;
	delete m_agent;
	m_agent = nullptr;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;
	m_window_dimensions = { float(getWindowWidth()), float(getWindowHeight()) };

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_agent->update(deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		quit();
	}
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	m_agent->draw(m_2dRenderer);

	if (m_agent->m_current_state == Agent::WANDER)
	{

		float start_x = m_agent->m_transform[2].x;
		float start_y = m_agent->m_transform[2].y;

		Vector2 end = { start_x, start_y };
		end += Vector2(m_agent->m_transform[1].x, m_agent->m_transform[1].y) * m_agent->wander_projection;

		float end_x = end.x;
		float end_y = end.y;

		m_2dRenderer->setRenderColour(0.0f, 1.0f, 0.0f);
		m_2dRenderer->drawCircle(end_x, end_y, m_agent->wander_radius);
		m_2dRenderer->setRenderColour(0.0f, 0.0f, 0.0f);
		m_2dRenderer->drawCircle(end_x, end_y, m_agent->wander_radius - 2);

		m_2dRenderer->setRenderColour(1.0f, 0.0f, 0.0f);
		m_2dRenderer->drawLine(start_x, start_y, end_x, end_y);

		m_2dRenderer->drawLine(m_agent->m_target_position.x, m_agent->m_target_position.y, end_x, end_y);
	}

	m_2dRenderer->setUVRect(0.0f, 0.0f, 1.0f, 1.0f);
	m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
	// Display the current agent state as text
	char current_agent_state[64];
	sprintf_s(current_agent_state, 64, "Current State: %i", m_agent->m_current_state);
	m_2dRenderer->drawText(m_font, current_agent_state, 0, 720 - 32);
	
	// Display amount of time left wandering
	char current_agent_time[64];
	sprintf_s(current_agent_time, 64, "Wandering time: %f", m_agent->current_wander_time);
	m_2dRenderer->drawText(m_font, current_agent_time, 0, 720 - 64);
	
	// done drawing sprites
	m_2dRenderer->end();
}