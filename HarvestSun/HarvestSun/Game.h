#pragma once
#include "Player.h"
#include "ResourceLoader.h"
#include "Tilemap.h"

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
	void loadMap(int mapID);
	Tilemap& getLayer(int layer);

	sf::RenderWindow m_window;
	sf::View m_view;
	Player m_player;
	ResourceLoader<sf::Texture, Textures::ID> m_texLoader;
	Tilemap m_mapLayerGround;
	Tilemap m_mapLayerMiddle;
	Tilemap m_mapLayerAbove;

	bool m_playerMovingUp = false;
	bool m_playerMovingDown = false;
	bool m_playerMovingRight = false;
	bool m_playerMovingLeft = false;

	const float FIXED_UPDATE_INTERVALL = 0.016f; // Amount of seconds to pass before each fixed update call
};

