#pragma once
#include "InputHandler.h"

class GameOverInputHandler : public InputHandler
{
private:
	bool m_XButtonPressed = false;
	bool m_BButtonPressed = false;

public:
	void handleGamepad(RenderWindow& window) override;
	void handleKeyPressed(Event& event,
		RenderWindow& window) override;

	void handleLeftClick(std::string& buttonInteractedWith,
		RenderWindow& window) override;
};
