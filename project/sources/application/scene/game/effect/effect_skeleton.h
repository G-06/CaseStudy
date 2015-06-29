//*****************************************************************************
//
// effect skeleton
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _EFFECT_SKELETON_H_
#define _EFFECT_SKELETON_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "effect.h"
#include "common/animation/animation.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class EffectSkeleton : public Effect
{
public:
	// constructor
	EffectSkeleton(void);

	// destructor
	virtual ~EffectSkeleton(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

private:
	static const s32 SKELETON_EFFECT_PATTERN = 8;
	static const Animation::DATA SKELETON_EFFECT[SKELETON_EFFECT_PATTERN];
	Sprite* sprite_;
	u32 frame_count_;
	Animation* animation_;
};

#endif	// _EFFECT_SKELETON_H_

//---------------------------------- EOF --------------------------------------
