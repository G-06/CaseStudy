//*****************************************************************************
//
// stage 4
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_FOUR_H_
#define _STAGE_FOUR_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "normal_stage.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
class StageFour : public NormalStage
{
public:
	// constructor
	StageFour(void);

	// destructor
	virtual ~StageFour(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// create factory
	StageFactory* CreateFactory(void)const;

	// accessor

private:

};

#endif	// _stage 1_H_

//---------------------------------- EOF --------------------------------------
