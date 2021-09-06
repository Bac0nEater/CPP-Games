#pragma once
#include "PlayableCharacter.h"

class Thomas : public PlayableCharacter
{
public:
	// A constructor specific to Thomas
	Thomas();

	// The overridden input handler for Thomas
	virtual bool handleInput();
};
