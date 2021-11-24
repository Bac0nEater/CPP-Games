#include "DevelopState.h"
#include "PhysicsEnginePlayMode.h"
#include <iostream>
#include "SoundEngine.h"
#include "WorldState.h"
#include "InvaderUpdateComponent.h"
#include "BulletUpdateComponent.h"

void PhysicsEnginePlayMode::detectInvaderCollisions(
	vector<GameObject>& objects,
	const vector<int>& bulletPositions)
{
	Vector2f offScreen(-1, -1);

	auto invaderIt = objects.begin();
	auto invaderEnd = objects.end();
	for (invaderIt;
		invaderIt != invaderEnd;
		++invaderIt)
	{
		if ((*invaderIt).isActive()
			&& (*invaderIt).getTag() == "invader")
		{
			auto bulletIt = objects.begin();
			// Jump to the first bullet
			advance(bulletIt, bulletPositions[0]);
			auto bulletEnd = objects.end();
			for (bulletIt;
				bulletIt != bulletEnd;
				++bulletIt)
			{
				if ((*invaderIt).getEncompassingRectCollider()
					.intersects((*bulletIt).getEncompassingRectCollider())
					&& (*bulletIt).getTag() == "bullet"
					&& static_pointer_cast<BulletUpdateComponent>(
						(*bulletIt).getFirstUpdateComponent())->m_BelongsToPlayer)
				{
					SoundEngine::playInvaderExplode();

					WorldState::SCORE++;
					WorldState::NUM_INVADERS--;

					(*invaderIt).getTransformComponent()
						->getLocation() = offScreen;
					(*bulletIt).getTransformComponent()
						->getLocation() = offScreen;
					(*invaderIt).setInactive();
				}
			}
		}
	}
}

void PhysicsEnginePlayMode::detectPlayerCollisionsAndInvaderDirection(
	vector<GameObject>& objects,
	const vector<int>& bulletPositions)
{
	Vector2f offScreen(-1, -1);

	FloatRect playerCollider = m_Player->getEncompassingRectCollider();
	shared_ptr<TransformComponent> playerTransform = m_Player->getTransformComponent();
	Vector2f playerLocation = playerTransform->getLocation();

	auto it3 = objects.begin();
	auto end3 = objects.end();
	for (it3;
		it3 != end3;
		++it3)
	{
		if ((*it3).isActive() &&
			(*it3).hasCollider() &&
			(*it3).getTag() != "Player")
		{
			// Get a reference to all the parts of
			// the current game object we might need
			FloatRect currentCollider = (*it3).getEncompassingRectCollider();
			shared_ptr<TransformComponent> currentTransform = (*it3).getTransformComponent();
			Vector2f currentLocation = currentTransform->getLocation();
			Vector2f currentSize = currentTransform->getSize();
			string currentTag = (*it3).getTag();

			// Detect collisions between objects
			// with the player
			if (currentCollider.intersects(playerCollider))
			{
				if (currentTag == "bullet")
				{
					SoundEngine::playPlayerExplode();
					WorldState::LIVES--;
					currentTransform->getLocation() = offScreen;
				}

				if (currentTag == "invader")
				{
					SoundEngine::playPlayerExplode();
					SoundEngine::playInvaderExplode();
					WorldState::LIVES--;
					WorldState::SCORE++;
					currentTransform->getLocation() = offScreen;
					(*it3).setInactive();
				}
			}

			// Handle the direction and descent
			// of the invaders
			// 
			// This is an invader
			if (currentTag == "invader")
			{
				// Currently no need to dropdown
				// and reverse from previous frame
				// or any hits this frame
				if (!m_NeedToDropDownAndReverse &&
					!m_InvaderHitWallThisFrame)
				{
					// The invader is passed its furthest
					// right position
					if (currentLocation.x >=
						WorldState::WORLD_WIDTH - currentSize.x)
					{
						// The invader is travelling
						// right so set a flag that
						// an invader has collided
						if (static_pointer_cast<InvaderUpdateComponent>
							((*it3).getFirstUpdateComponent())->
							isMovingRight())
						{

							m_InvaderHitWallThisFrame = true;
						}
					}
					// The invader is past its furthest
					// left position
					else if (currentLocation.x < 0)
					{
						// The invader is travelling
						// left so set a flag that an
						// invader has collided
						if (!static_pointer_cast<InvaderUpdateComponent>
							((*it3).getFirstUpdateComponent())
							->isMovingRight())
						{
							m_InvaderHitWallThisFrame = true;
						}
					}
				}
				else if (m_NeedToDropDownAndReverse &&
					!m_InvaderHitWallPreviousFrame)
				{
					// Drop down and reverse has been set
					if ((*it3).hasUpdateComponent())
					{
						// Drop down and reverse
						static_pointer_cast<InvaderUpdateComponent>
							((*it3).getFirstUpdateComponent())
							->dropDownAndReverse();
					}

				}
			}
		}
	}
}

void PhysicsEnginePlayMode::handleInvaderDirection()
{
	if (m_InvaderHitWallThisFrame) {
		m_NeedToDropDownAndReverse = true;
		m_InvaderHitWallThisFrame = false;
	}
	else {
		m_NeedToDropDownAndReverse = false;
	}
}

void PhysicsEnginePlayMode::initilize(GameObjectSharer& gos) {
	m_PUC = static_pointer_cast<PlayerUpdateComponent>(
		gos.findFirstObjectWithTag("Player")
		.getComponentByTypeAndSpecificType("update", "player"));
	m_Player = &gos.findFirstObjectWithTag("Player");
}

void PhysicsEnginePlayMode::detectCollisions(
	vector<GameObject>& objects,
	const vector<int>& bulletPositions)
{
	detectInvaderCollisions(objects, bulletPositions);
	detectPlayerCollisionsAndInvaderDirection(objects, bulletPositions);
	handleInvaderDirection();
}
