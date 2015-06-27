//*****************************************************************************
//
// stage 1
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_EIGHT_H_
#define _STAGE_EIGHT_H_

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
class StageEight : public NormalStage
{
public:
	// constructor
	StageEight(void);

	// destructor
	virtual ~StageEight(void);

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

#endif	// _stage 8_H_

//---------------------------------- EOF --------------------------------------
