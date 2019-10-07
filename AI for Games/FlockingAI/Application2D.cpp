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
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_window_dimensions = { float(getWindowWidth()), float(getWindowHeight()) };

	m_agent = new Agent(200.0f, 200.0f);
	m_agent->AddBehaviour(new KeyboardBehaviour());
	m_agent->m_maxSpeed = 250.0f;

	m_flock = new Flock();
	m_flock->m_agent = m_agent;
	//m_flock->m_input = ;

	m_flock->create_boids(m_2dRenderer, 100, m_window_dimensions);

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
	m_flock->update(deltaTime, m_window_dimensions);

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

	m_2dRenderer->setRenderColour(0.0f, 0.3f, 1.0f);
	m_agent->draw(m_2dRenderer);

	m_flock->draw();

	m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f);
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	// done drawing sprites
	m_2dRenderer->end();
}