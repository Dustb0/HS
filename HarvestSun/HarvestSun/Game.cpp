#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

	loadMap(1);

	// Assign texture to sprite
	m_player.setTexture(m_texLoader.get(Textures::Jack));

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

void Game::loadMap(int mapID)
{
	// Put together filename
	std::ostringstream oss;
	oss << "Data/Maps/Map" << mapID << ".txt";

	// Open file
	std::ifstream mapFile;
	mapFile.open(oss.str());

	// Create variables for reading through the file
	std::string line;
	int mapWidth = 0;
	int mapHeight = 0;
	int level[3][200];
	int currentLayer = 0;
	int rowCounter = 0;

	// Read through the file
	while (getline(mapFile, line))
	{
		if (!line.compare(0, 5, "BEGIN"))
		{
			// Read tilemap-ID and assign texture
			Textures::ID id = (Textures::ID) std::stoi(line.substr(6, line.length() - 1));
			getLayer(currentLayer).setTexture(m_texLoader.get(id));

			//std::cout << "Layer #" << currentLayer << ": " << &getLayer(currentLayer) << "\n";
		}
		else if (!line.compare(0, 3, "END"))
		{
			// Increase layer count
			++currentLayer;
			rowCounter = 0;
		}
		else if (!line.compare(0, 3, "MAP"))
		{
			// Read in map width and height
			std::istringstream ss(line.substr(4, line.length() - 1));
			std::string num;
			int rowCounter = 0;
			while (getline(ss, num, ','))
			{
				if (rowCounter == 0) mapWidth = std::stoi(num);
				else if (rowCounter == 1) mapHeight = std::stoi(num);
				++rowCounter;
			}
		}
		else
		{
			// Read in tilemap data
			std::istringstream ss(line);
			std::string tile;
			while (getline(ss, tile, ','))
			{
				level[currentLayer][rowCounter] = std::stoi(tile);
				++rowCounter;
			}
		}
	}

	// Close file
	mapFile.close();

	std::cout << level[1][0];

	// Load map layers
	m_mapLayerGround.loadMapData(level[0], mapWidth, mapHeight);
	m_mapLayerMiddle.loadMapData(level[1], mapWidth, mapHeight);
	m_mapLayerAbove.loadMapData(level[2], mapWidth, mapHeight);
}

Tilemap& Game::getLayer(int layer)
{
	switch (layer)
	{
	case 0: return m_mapLayerGround;
	case 1: return m_mapLayerMiddle;
	case 2: return m_mapLayerAbove;
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
	m_mapLayerGround.update();
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
	m_window.draw(m_mapLayerGround);
	m_window.draw(m_mapLayerMiddle);
	m_window.draw(m_player);
	m_window.draw(m_mapLayerAbove);

	// Display
	m_window.display();
}