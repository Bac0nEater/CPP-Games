#include "SelectInputHandler.h"
#include "SoundEngine.h"
#include "WorldState.h"
#include <iostream>

int WorldState::WAVE_NUMBER;

void SelectInputHandler::handleGamepad(RenderWindow& window)
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
		getPointerToScreenManagerRemoteControl()
			->loadLevelInPlayMode("level1");
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

		// Quit the game
		SoundEngine::playClick();
		window.close();
	}
}

void SelectInputHandler::handleKeyPressed(
	Event& event, RenderWindow& window)
{
	// Quit the game
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		SoundEngine::playClick();
		window.close();
	}
}

void SelectInputHandler::handleLeftClick(
	std::string& buttonInteractedWith, RenderWindow& window)
{
	if (buttonInteractedWith == "Play") {
		SoundEngine::playClick();
		WorldState::WAVE_NUMBER = 0;
		getPointerToScreenManagerRemoteControl()
			->loadLevelInPlayMode("level1");
	}

	if (buttonInteractedWith == "Quit") {
		SoundEngine::playClick();
		window.close();
	}
}
