//*****************************************************************************
//
// gimmick check point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _GIMMICK_CHECK_POINT_H_
#define _GIMMICK_CHECK_POINT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class ObjectCheckPoint;

//*****************************************************************************
// class definition
//*****************************************************************************
class GimmickCheckPoint : public Gimmick
{
public:
	// constructor
	GimmickCheckPoint(void);

	// destructor
	virtual ~GimmickCheckPoint(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// accessor

private:
	ObjectCheckPoint* object_check_point_;
};

#endif	// _GIMMICK_CHECK_POINT_H_

//---------------------------------- EOF --------------------------------------