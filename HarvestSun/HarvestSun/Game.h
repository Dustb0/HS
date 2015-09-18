#pragma once
#include "Player.h"
#include "ResourceLoader.h"

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void update(float deltaTime);
	void fixedUpdate(float deltaTime);
	void render();
	void processEvents();
	void handlePlayerInput(sf::Keyboard::Key key, bool pressed);

	sf::RenderWindow m_window;
	Player m_player;
	ResourceLoader<sf::Texture, Textures::ID> m_texLoader;

	bool m_playerMovingUp = false;
	bool m_playerMovingDown = false;
	bool m_playerMovingRight = false;
	bool m_playerMovingLeft = false;

	const float FIXED_UPDATE_INTERVALL = 0.016f; // Amount of seconds to pass before each fixed update call
};

