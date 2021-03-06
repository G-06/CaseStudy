//*****************************************************************************
//
// gimmick check point
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "gimmick_check_point.h"
#include "object/object_check_point.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
GimmickCheckPoint::GimmickCheckPoint(void)
	:Gimmick(TYPE_CHECK_POINT)
{
	data_._priority = 0;
	data_._hit = false;
	size_ = D3DXVECTOR2(128.0f,128.0f);
}

//=============================================================================
// destructor
//=============================================================================
GimmickCheckPoint::~GimmickCheckPoint(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool GimmickCheckPoint::Initialize(void)
{
	object_check_point_ = new ObjectCheckPoint();
	object_check_point_->Initialize();

	onece_ = false;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void GimmickCheckPoint::Uninitialize(void)
{
	SafeRelease(object_check_point_);
}

//=============================================================================
// update
//=============================================================================
void GimmickCheckPoint::Update(void)
{
	if(onece_ == false)
	{
		if(data_._hit == true)
		{
			object_check_point_->Hit();
			onece_ = true;
		}
	}
	object_check_point_->Update();
}

//=============================================================================
// draw
//=============================================================================
void GimmickCheckPoint::Draw(void)
{
	object_check_point_->__position(position_ - offset_position_);
	object_check_point_->Draw();
}

//=============================================================================
// get pointer
//=============================================================================
void* GimmickCheckPoint::GetPointer(void)
{
	return &data_;
}




//---------------------------------- EOF --------------------------------------
