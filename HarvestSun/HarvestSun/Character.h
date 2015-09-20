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

	virtual void update(float deltaTime)
	{

	}

	virtual void fixedUpdate(float deltaTime)
	{

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
			// Check if we need to advance the move-animation
			if (m_moveAnim)
			{
				// Increase move-timer
				m_currentlyMovingSince += deltaTime;

				// Check if we need to jump to the next animation-frame
				if (m_currentlyMovingSince >= m_moveAnimInterval)
				{
					// Advance the moveanim-index
					++m_moveAnimIndex;

					if (m_moveAnimIndex > 3) m_moveAnimIndex = 0;

					// Reset the timer
					m_currentlyMovingSince = 0;
				}

				m_wasMovingLastUpdate = true;
			}

			// Determine direciton
			if (offset.y > 0) m_lastDirection = 0;
			else if (offset.y < 0) m_lastDirection = 3;
			else if (offset.x < 0) m_lastDirection = 1;
			else if (offset.x > 0) m_lastDirection = 2;

			setFacingDirection(m_lastDirection);

			// Move the sprite
			m_sprite.move(offset * m_moveSpeed * deltaTime);
		}
		else
		{
			m_moveAnimIndex = 0;
			m_currentlyMovingSince = 0;
			m_wasMovingLastUpdate = false;
			setSubTexture(0, m_lastDirection);
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
	// Determines if the character was moving in the last update
	bool m_wasMovingLastUpdate;
	// The amount of time we've been moving, needed to animate the movement-cycle
	float m_currentlyMovingSince;
	// Current display-index of the move animation, used for locating the correct sub-sprite
	int m_moveAnimIndex;
	// The amount of secs in which the move-animation jumps to the next anim-frame
	float m_moveAnimInterval = 0.25f;
	// The direction in which the character last moved
	int m_lastDirection;

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

