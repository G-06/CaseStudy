//*****************************************************************************
//
// stage 3
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _STAGE_THREE_H_
#define _STAGE_THREE_H_

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
class StageThree : public NormalStage
{
public:
	// constructor
	StageThree(void);

	// destructor
	virtual ~StageThree(void);

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