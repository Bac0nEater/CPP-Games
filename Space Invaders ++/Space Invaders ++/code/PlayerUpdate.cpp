#include "PlayerUpdateComponent.h"
#include "WorldState.h"

void PlayerUpdateComponent::update(float fps)
{
	if (sf::Joystick::isConnected(0))
	{
		m_TC->getLocation().x +=
			((m_Speed / 100) * m_XExtent) * fps;

		m_TC->getLocation().y +=
			((m_Speed / 100) * m_YExtent) * fps;
	}

	// Left and right (Horizontal)
	if (m_IsHoldingLeft && m_IsHoldingRight)
	{
		// if both horizontal keys are holding,
		// only the recent one take the effect
		if (m_RecentHorizontalIsLeft)
		{
			m_TC->getLocation().x -= m_Speed * fps;
		}
		else
		{
			m_TC->getLocation().x += m_Speed * fps;
		}
	}
	else if (m_IsHoldingLeft)
	{
		m_TC->getLocation().x -= m_Speed * fps;
	}
	else if (m_IsHoldingRight)
	{
		m_TC->getLocation().x += m_Speed * fps;
	}

	// Up and down (Vertical)
	if (m_IsHoldingUp && m_IsHoldingDown)
	{
		// if both vertical keys are holding,
		// only the recent one take the effect
		if (m_RecentVerticalIsUp)
		{
			m_TC->getLocation().y -= m_Speed * fps;
		}
		else
		{
			m_TC->getLocation().y += m_Speed * fps;
		}
	}
	else if (m_IsHoldingUp)
	{
		m_TC->getLocation().y -= m_Speed * fps;
	}
	else if (m_IsHoldingDown)
	{
		m_TC->getLocation().y += m_Speed * fps;
	}

	// Update the collider
	m_RCC->setOrMoveCollider(
		m_TC->getLocation().x, m_TC->getLocation().y,
		m_TC->getSize().x, m_TC->getSize().y);

	// Make sure the ship doesn't go outside the allowed area
	if (m_TC->getLocation().x >
		WorldState::WORLD_WIDTH - m_TC->getSize().x)
	{
		m_TC->getLocation().x =
			WorldState::WORLD_WIDTH - m_TC->getSize().x;
	}
	else if (m_TC->getLocation().x < 0)
	{
		m_TC->getLocation().x = 0;
	}

	if (m_TC->getLocation().y >
		WorldState::WORLD_HEIGHT - m_TC->getSize().y)
	{
		m_TC->getLocation().y =
			WorldState::WORLD_HEIGHT - m_TC->getSize().y;
	}
	else if (m_TC->getLocation().y <
		WorldState::WORLD_HEIGHT / 2)
	{
		m_TC->getLocation().y =
			WorldState::WORLD_HEIGHT / 2;
	}
}

void PlayerUpdateComponent::updateShipTravelWithController(float x, float y)
{
	m_XExtent = x;
	m_YExtent = y;
}

void PlayerUpdateComponent::moveLeft()
{
	m_IsHoldingLeft = true;
	m_RecentHorizontalIsLeft = true;
}
void PlayerUpdateComponent::moveRight()
{
	m_IsHoldingRight = true;
	m_RecentHorizontalIsLeft = false;
}
void PlayerUpdateComponent::moveUp()
{
	m_IsHoldingUp = true;
	m_RecentVerticalIsUp = true;
}
void PlayerUpdateComponent::moveDown()
{
	m_IsHoldingDown = true;
	m_RecentVerticalIsUp = false;
}

void PlayerUpdateComponent::stopLeft()
{
	m_IsHoldingLeft = false;
}
void PlayerUpdateComponent::stopRight()
{
	m_IsHoldingRight = false;
}
void PlayerUpdateComponent::stopUp()
{
	m_IsHoldingUp = false;
}
void PlayerUpdateComponent::stopDown()
{
	m_IsHoldingDown = false;
}
