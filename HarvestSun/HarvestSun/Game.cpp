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

	// Load resources
	m_texLoader.Load(Textures::Jack, "Data/Textures/Hero.png");
	
	// Assign texture to sprite
	m_player.setTexture(m_texLoader.Get(Textures::Jack));

	sf::Clock clock;
	float secsSinceLastUpdate = 0;

	while (m_window.isOpen())
	{
		// Measure passed time since last update
		sf::Time deltaTime = clock.restart();

		// Accumulate passed seconds for fixed update
		secsSinceLastUpdate += deltaTime.asSeconds();

		ProcessEvents();
		Update(deltaTime.asSeconds());

		// Check fixed update
		if (secsSinceLastUpdate >= FIXED_UPDATE_INTERVALL)
		{
			FixedUpdate(secsSinceLastUpdate);
			secsSinceLastUpdate = 0;
		}

		Render();
	}
}

void Game::ProcessEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			HandlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			HandlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Game::HandlePlayerInput(sf::Keyboard::Key key, bool pressed)
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

void Game::Update(float deltaTime)
{
	
}

void Game::FixedUpdate(float deltaTime)
{
	// Translate input to player movement
	sf::Vector2f mov(0.0f, 0.0f);

	if (m_playerMovingUp) mov.y -= 1.0f;
	if (m_playerMovingDown) mov.y += 1.0f;
	if (m_playerMovingLeft) mov.x -= 1.0f;
	if (m_playerMovingRight) mov.x += 1.0f;

	//std::cout << "Mov: X:" << mov.x << " Y:" << mov.y << "\n";

	m_player.move(mov * m_playerSpeed * deltaTime);
}

void Game::Render()
{
	// Clear window
	m_window.clear(sf::Color::Black);

	// Draw stuff
	m_window.draw(m_player);

	// Display
	m_window.display();
}