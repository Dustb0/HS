#include "Game.h"
#include <iostream>

Game::Game() : m_window(sf::VideoMode(800, 600), "Harvest Sun"), m_player(), m_texLoader()
{
}

Game::~Game()
{
}

void Game::Run()
{
	// Initialize window
	m_window.setVerticalSyncEnabled(true);

	// Get view reference
	m_view = m_window.getView();

	// Load resources
	m_texLoader.load(Textures::Jack, "Data/Textures/Hero.png");
	m_texLoader.load(Textures::TestMap, "Data/Textures/Map.png");
	
	// Assign texture to sprite
	m_player.setTexture(m_texLoader.get(Textures::Jack));

	// Assign texture to map
	m_map.setTexture(m_texLoader.get(Textures::TestMap));

	// Load level data
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 3, 0,
		0, 1, 1, 0, 0, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0,
		2, 0, 1, 0, 0, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 2, 2,
		0, 0, 1, 0, 0, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
		0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
	};
	m_map.loadMapData(level, 18, 10);

	sf::Clock clock;
	float secsSinceLastUpdate = 0;

	while (m_window.isOpen())
	{
		// Measure passed time since last update
		sf::Time deltaTime = clock.restart();

		// Accumulate passed seconds for fixed update
		secsSinceLastUpdate += deltaTime.asSeconds();

		processEvents();
		update(deltaTime.asSeconds());

		// Check fixed update
		if (secsSinceLastUpdate >= FIXED_UPDATE_INTERVALL)
		{
			fixedUpdate(secsSinceLastUpdate);
			secsSinceLastUpdate = 0;
		}

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool pressed)
{
	switch (key)
	{
	case sf::Keyboard::W:
		m_playerMovingUp = pressed;
		break;

	case sf::Keyboard::S:
		m_playerMovingDown = pressed;
		break;

	case sf::Keyboard::D:
		m_playerMovingRight = pressed;
		break;

	case sf::Keyboard::A:
		m_playerMovingLeft = pressed;
		break;
	}
}

void Game::update(float deltaTime)
{
	
}

void Game::fixedUpdate(float deltaTime)
{
	// Translate input to player movement
	sf::Vector2f mov(0.0f, 0.0f);

	if (m_playerMovingUp) mov.y -= 1.0f;
	if (m_playerMovingDown) mov.y += 1.0f;
	if (m_playerMovingLeft) mov.x -= 1.0f;
	if (m_playerMovingRight) mov.x += 1.0f;

	m_player.move(mov, deltaTime); 
	m_player.fixedUpdate(deltaTime);

	//m_view.move(0.0f, 10.0f * deltaTime);
	m_window.setView(m_view);
}

void Game::render()
{
	// Clear window
	m_window.clear(sf::Color::Black);

	// Draw stuff
	m_window.draw(m_map);
	m_window.draw(m_player);

	// Display
	m_window.display();
}