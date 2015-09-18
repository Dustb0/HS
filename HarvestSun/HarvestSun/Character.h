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

		setFacingDirection(0); // Facing down
	}

	void move(const sf::Vector2f &offset, float deltaTime)
	{
		// Determine direciton
		if (offset.y > 0) setFacingDirection(0);
		else if (offset.y < 0) setFacingDirection(3);
		else if (offset.x < 0) setFacingDirection(1);
		else if (offset.x > 0) setFacingDirection(2);

		// Move the sprite
		m_sprite.move(offset * m_moveSpeed * deltaTime);
	}

	void setSubTexture(int column, int row)
	{
		// Each loaded character texture is 3 tiles wide and 4 tiles high, so divide by that portion
		m_sprite.setTextureRect(sf::IntRect(column * m_spriteRect.x, row * m_spriteRect.y, m_spriteRect.x, m_spriteRect.y));
	}

private:
	// Flag if the character is currently active
	bool m_enabled;
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
		
		// Set sub texture to first image of the facing direciton
		setSubTexture(0, m_facingDirection);
	}

};

