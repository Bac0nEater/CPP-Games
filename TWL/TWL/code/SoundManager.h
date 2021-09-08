#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class SoundManager
{
private:
	// The buffers
	SoundBuffer m_FireBuffer;
	SoundBuffer m_FallInFireBuffer;
	SoundBuffer m_FallInWaterBuffer;
	SoundBuffer m_JumpBuffer;
	SoundBuffer m_ReachGoalBuffer;

	// The Sounds
	Sound m_Fire1Sound;
	Sound m_Fire2Sound;
	Sound m_Fire3Sound;
	Sound m_FallInFireSound;
	Sound m_FallInWaterSound;
	Sound m_JumpSound;
	Sound m_ReachGoalSound;

	// Which sound should we use next, fire 1, 2 or 3
	int m_NextSound = 1;

	// Locations of fire 1, 2, and 3
	vector <Vector2f> m_FireLocations;

public:
	SoundManager();

	// update/stop the fire sound if necessary
	void updateFire(FloatRect listenerLocation);

	// play spatialized sound effects
	void playFire(Vector2f emitterLocation, Vector2f listenerLocation);

	// play "normal" sound effects
	void playFallInFire();
	void playFallInWater();
	void playJump();
	void playReachGoal();
};
