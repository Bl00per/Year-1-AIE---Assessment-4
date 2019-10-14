#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "Vector2.h"
#include <queue>

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

	int spacing = 80;
	int width = 15;
	int height = 8;

	graph<Vector2>* m_graph;

	std::queue<node<Vector2>*> m_selection_queue;

	float m_timer;
};