#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>

class Character : public sf::Drawable, private sf::NonCopyable
{

public:
	Character()
	{
	}

	~Character()
	{
	}

	typedef std::unique_ptr<Character> Ptr;

	virtual void fixedUpdate(float deltaTime)
	{
		// Check if we need to play the move animation
		if (m_moveAnimIndex == 0)
		{
			// Face direction in which the player is moving
			setFacingDirection(m_currentDirection);
		}
		else
		{
			// Move animation currently playing
			m_moveAnimTimer += deltaTime;

			// Check if we need to advance to the next animation frame
			if (m_moveAnimTimer >= m_moveAnimInterval)
			{
				setSubTextureWithMoveAnim(m_currentDirection);

				m_moveAnimTimer = 0;
				++m_moveAnimIndex;
				if (m_moveAnimIndex > 3) m_moveAnimIndex = 0;
			}
		}
		
	}

	void setEnabled(bool val) { m_enabled = val; }
	bool getEnabled() { return m_enabled; }

	void setTexture(const sf::Texture &texture, bool resetRect = false)
	{
		m_sprite.setTexture(texture, resetRect);
		
		// Calcualte sprite rect
		m_spriteRect = texture.getSize();
		m_spriteRect.x /= 3;
		m_spriteRect.y /= 4;

		// Set bounds to the sprite's center
		m_sprite.setOrigin(m_spriteRect.x / 2.0f, m_spriteRect.y / 2.0f);

		setFacingDirection(0); // Facing down
	}

	void move(const sf::Vector2f &offset, float deltaTime)
	{
		// Check for move animation & determine if the character was moving in this frame
		if (offset.x != 0 || offset.y != 0)
		{
			// Determine if move animation needs to be started, if it isn't playing (index == 0)
			if (m_moveAnim && m_moveAnimIndex == 0) m_moveAnimIndex = 1;

			// Determine direciton
			if (offset.y > 0) m_currentDirection = 0;
			else if (offset.y < 0) m_currentDirection = 3;
			else if (offset.x < 0) m_currentDirection = 1;
			else if (offset.x > 0) m_currentDirection = 2;

			// Move the sprite
			m_sprite.move(offset * m_moveSpeed * deltaTime);
		}
	}

	void setSubTexture(int column, int row)
	{
		// Each loaded character texture is 3 tiles wide and 4 tiles high, so divide by that portion
		m_sprite.setTextureRect(sf::IntRect(column * m_spriteRect.x, row * m_spriteRect.y, m_spriteRect.x, m_spriteRect.y));
	}

	void setSubTextureWithMoveAnim(int row)
	{
		int col = 0;

		switch (m_moveAnimIndex)
		{
		case 0:
		case 2:
			col = 0;
			break;
		case 1:
			col = 1;
			break;
		case 3:
			col = 2;
		}

		setSubTexture(col, row);
	}

private:
	// Flag if the character is currently active
	bool m_enabled;
	// Flag if the character has an animated move-cycle
	bool m_moveAnim = true;
	// Current display-index of the move animation, used for locating the correct sub-sprite
	int m_moveAnimIndex;
	float m_moveAnimTimer;
	// The amount of secs in which the move-animation jumps to the next anim-frame
	float m_moveAnimInterval = 0.25f;
	// The direction in which the character is moving/facing
	int m_currentDirection;

	// The internal sprite
	sf::Sprite m_sprite;
	// The size of a single sprite-cell in the texture
	sf::Vector2u m_spriteRect;
	// The direction the character currently faces (0 = Down, 1 = Left, 2 = Right, 3 = Up)
	int m_facingDirection;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_sprite, states);
	}

protected:
	float m_moveSpeed = 100.0f;

	void setFacingDirection(int value)
	{
		m_facingDirection = value;
		
		// Set sub texture to first image of the facing direciton (if we hit index==2 then display the first frame again)
		setSubTextureWithMoveAnim(m_facingDirection);
	}

};

