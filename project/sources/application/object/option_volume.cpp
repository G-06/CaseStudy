//*****************************************************************************
//
// option volume
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "option_volume.h"
#include "render/sprite.h"
#include "system/system.h"
#include "option.h"

//=============================================================================
// constructor
//=============================================================================
OptionVolume::OptionVolume(void)
{
}

//=============================================================================
// destructor
//=============================================================================
OptionVolume::~OptionVolume(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool OptionVolume::Initialize(void)
{
	volume_gage_ = new Sprite();
	volume_gage_->Initialize();
	volume_gage_->__size(Option::DEFAULT_MENU_SIZE);
	volume_gage_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width(),(f32)GET_SYSTEM.__window()->__height()));
	volume_gage_->__texture_id(Texture::TEXTURE_ID_OPTION_BG);
	volume_gage_->__point(Sprite::POINT_CENTER);
	volume_gage_->__division_height(2);
	volume_gage_->__division_width(5);
	volume_gage_->__index(0);
	volume_gage_->SetParameter();
	
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void OptionVolume::Uninitialize(void)
{
	SafeRelease(volume_gage_);
}

//=============================================================================
// update
//=============================================================================
void OptionVolume::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void OptionVolume::Draw(void)
{
	volume_gage_->Draw();
}

//=============================================================================
// select
//=============================================================================
void OptionVolume::Adjustvolume(u32 volume)
{
	volume_gage_->__index(volume);
	volume_gage_->SetParameter();
}

//---------------------------------- EOF --------------------------------------
