#pragma once

#include "ComplexSprite.h"
#include "BasePilot.h"
#include "Character.h"


class ClientCharacter : public Character
{
	/*----------------------------------------------------------------------------------------
	Instance Fields
	----------------------------------------------------------------------------------------*/
private:


	/*----------------------------------------------------------------------------------------
	Resource Management
	----------------------------------------------------------------------------------------*/
public:
	/** Default constructor. */
	explicit ClientCharacter(BasePilot* basePilot, int networkingID);

	/*----------------------------------------------------------------------------------------
	Instance Getter Methods
	----------------------------------------------------------------------------------------*/
public:


	/*----------------------------------------------------------------------------------------
	Instance Setter Methods
	----------------------------------------------------------------------------------------*/
public:


	/*----------------------------------------------------------------------------------------
	Instance Methods
	----------------------------------------------------------------------------------------*/
public:
	void onUpdate(int ticks);
	void onEnd ();
	bool playRunAnimation ();
	bool endRunAnimation ();
	bool playMeleeAttackAnimation ();
	bool playRangeAttackAnimation ();
	bool playHurtAnimation ();

private:
	/*--------------------
	Player Animation Logic
	--------------------*/
};
