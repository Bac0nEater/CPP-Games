#include "GameOverInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include <iostream>

void GameOverInputHandler::handleGamepad(RenderWindow& window)
{
	// Has the player pressed the X button? XBox One controller
	if (Joystick::isButtonPressed(0, 2))
	{
		m_XButtonPressed = true;
	}

	// Has player just released the X button?
	if (!Joystick::isButtonPressed(0, 2) && m_XButtonPressed)
	{
		m_XButtonPressed = false;

		// Play button is clicked
		SoundEngine::playClick();
		WorldState::WAVE_NUMBER = 0;
		getPointerToScreenManagerRemoteControl()->
			loadLevelInPlayMode("level1");
	}

	// Has the player pressed the B button? XBox One controller
	if (Joystick::isButtonPressed(0, 1))
	{
		m_BButtonPressed = true;
	}

	// Has player just released the B button?
	if (!Joystick::isButtonPressed(0, 1) && m_BButtonPressed)
	{
		m_BButtonPressed = false;

		// Home button is clicked
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->
			SwitchScreens("Select");
	}
}

void GameOverInputHandler::handleKeyPressed(
	Event& event, RenderWindow& window)
{
	if (event.key.code == Keyboard::Escape)
	{
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->
			SwitchScreens("Select");
	}
}

void GameOverInputHandler::handleLeftClick(
	std::string& buttonInteractedWith, RenderWindow& window)
{
	if (buttonInteractedWith == "Play") {
		SoundEngine::playClick();
		WorldState::WAVE_NUMBER = 0;
		getPointerToScreenManagerRemoteControl()->
			loadLevelInPlayMode("level1");
	}
	else if (buttonInteractedWith == "Home") {
		SoundEngine::playClick();
		getPointerToScreenManagerRemoteControl()->
			SwitchScreens("Select");
	}
}
