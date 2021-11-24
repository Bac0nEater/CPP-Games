#pragma once
#include "InputHandler.h"
#include "PlayerUpdateComponent.h"
#include "TransformComponent.h"

class GameScreen;
class GameInputHandler : public InputHandler
{
private:
	shared_ptr<PlayerUpdateComponent> m_PUC;
	shared_ptr<TransformComponent> m_PTC;

	bool m_AButtonPressed = false;
	bool m_BButtonPressed = false;

	void shootABullet();

public:
	void initialize();
	void handleGamepad(RenderWindow& window) override;
	void handleKeyPressed(Event& event,
		RenderWindow& window) override;

	void handleKeyReleased(Event& event,
		RenderWindow& window) override;
};
