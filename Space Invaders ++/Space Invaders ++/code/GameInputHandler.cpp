#include "GameInputHandler.h"
#include "SoundEngine.h"
#include "GameScreen.h"

class BulletSpawner;

void GameInputHandler::initialize()
{
}

void GameInputHandler::handleGamepad()
{
}

void GameInputHandler::handleKeyPressed(
	Event& event, RenderWindow& window)
{
	// Handle key presses
	if (event.key.code == Keyboard::Escape)
	{
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->
			SwitchScreens("Select");
	}

	if (event.key.code == Keyboard::Left)
	{
		m_PUC->moveLeft();
	}

	if (event.key.code == Keyboard::Right)
	{
		m_PUC->moveRight();
	}

	if (event.key.code == Keyboard::Up)
	{
		m_PUC->moveUp();
	}

	if (event.key.code == Keyboard::Down)
	{
		m_PUC->moveDown();
	}
}

void GameInputHandler::handleKeyReleased(
	Event& event, RenderWindow& window)
{
	if (event.key.code == Keyboard::Left)
	{
		m_PUC->stopLeft();
	}

	else if (event.key.code == Keyboard::Right)
	{
		m_PUC->stopRight();
	}

	else if (event.key.code == Keyboard::Up)
	{
		m_PUC->stopUp();
	}

	else if (event.key.code == Keyboard::Down)
	{
		m_PUC->stopDown();
	}

	else if (event.key.code == Keyboard::Space)
	{
		// Shoot a bullet
		SoundEngine::playShoot();
		Vector2f spawnLocation;
		spawnLocation.x = m_PTC->getLocation().x + m_PTC->getSize().x / 2;
		spawnLocation.y = m_PTC->getLocation().y;

		static_cast<GameScreen*>(getmParentScreen())->
			spawnBullet(spawnLocation, true);
	}
}
