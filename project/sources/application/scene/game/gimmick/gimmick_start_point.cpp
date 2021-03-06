//*****************************************************************************
//
// gimmick start point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick_start_point.h"
#include "object/object_start_point.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
GimmickStartPoint::GimmickStartPoint(void)
	:Gimmick(TYPE_START_POINT)
{
}

//=============================================================================
// destructor
//=============================================================================
GimmickStartPoint::~GimmickStartPoint(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GimmickStartPoint::Initialize(void)
{
	object_start_point_ = new ObjectStartPoint();
	object_start_point_->Initialize();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GimmickStartPoint::Uninitialize(void)
{
	SafeRelease(object_start_point_);
}

//=============================================================================
// update
//=============================================================================
void GimmickStartPoint::Update(void)
{
	object_start_point_->Update();
}

//=============================================================================
// draw
//=============================================================================
void GimmickStartPoint::Draw(void)
{
	object_start_point_->__position(position_ - offset_position_);
	//object_start_point_->Draw();
}

//---------------------------------- EOF --------------------------------------
