#pragma once
#include <SFML/Graphics.hpp>

class Tilemap : public sf::Drawable
{
public:
	Tilemap()
	{

	}

	~Tilemap()
	{

	}

	void setTexture(const sf::Texture &texture)
	{
		m_texture = texture;
	}

	void loadMapData(const int* tileData, unsigned int width, unsigned int height)
	{
		// Resize the vertex array to fit the level size
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		// Populate the vertex array, with one quad per tile
		for (unsigned int i = 0; i < width; ++i)
		{
			for (unsigned int j = 0; j < height; ++j)
			{
				// Get the current tile number
				int tileNumber = tileData[i + j * width];

				// Find its position in the tileset texture
				int tu = tileNumber % (m_texture.getSize().x / TILESIZE);
				int tv = tileNumber / (m_texture.getSize().x / TILESIZE);

				// Get a pointer to the current tile's quad
				sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * TILESIZE, j * TILESIZE);
				quad[1].position = sf::Vector2f((i + 1) * TILESIZE, j * TILESIZE);
				quad[2].position = sf::Vector2f((i + 1) * TILESIZE, (j + 1) * TILESIZE);
				quad[3].position = sf::Vector2f(i * TILESIZE, (j + 1) * TILESIZE);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * TILESIZE, tv * TILESIZE);
				quad[1].texCoords = sf::Vector2f((tu + 1) * TILESIZE, tv * TILESIZE);
				quad[2].texCoords = sf::Vector2f((tu + 1) * TILESIZE, (tv + 1) * TILESIZE);
				quad[3].texCoords = sf::Vector2f(tu * TILESIZE, (tv + 1) * TILESIZE);
			}
		}
	}

private:
	sf::VertexArray m_vertices;
	sf::Texture m_texture;
	const int TILESIZE = 32;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the tileset texture
		states.texture = &m_texture;

		// draw the vertex array
		target.draw(m_vertices, states);
	}
};

