#pragma once

#include "Application.h"
#include "Agent.h"
#include "Flock.h"
#include "KeyboardBehaviour.h"
#include "Vector2.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	Agent* m_agent;
	
	Flock* m_flock;

	Vector2 m_window_dimensions;


	float m_timer;
};