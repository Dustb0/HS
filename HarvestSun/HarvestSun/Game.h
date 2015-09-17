#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceLoader.h"

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Render();
	void ProcessEvents();
	void HandlePlayerInput(sf::Keyboard::Key key, bool pressed);

	sf::RenderWindow m_window;
	sf::Texture m_playerTex;
	sf::Sprite m_player;
	ResourceLoader<sf::Texture, Textures::ID> m_texLoader;

	float m_playerSpeed = 100.0f;
	bool m_playerMovingUp = false;
	bool m_playerMovingDown = false;
	bool m_playerMovingRight = false;
	bool m_playerMovingLeft = false;

	const float FIXED_UPDATE_INTERVALL = 0.016f; // Amount of seconds to pass before each fixed update call
};

