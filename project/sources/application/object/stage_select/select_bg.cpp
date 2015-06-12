//*****************************************************************************
//
// stage select bg
//
// Author		: taichi kitazawa
//
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "select_bg.h"
#include "render/sprite.h"
#include "system/system.h"

//=============================================================================
// constructor
//=============================================================================
SelectBg::SelectBg(void)
{
}

//=============================================================================
// destructor
//=============================================================================
SelectBg::~SelectBg(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool SelectBg::Initialize(void)
{
	bg_ = new Sprite();
	bg_->Initialize();
	bg_->__size(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width(),(f32)GET_SYSTEM.__window()->__height()));
	bg_->__position(D3DXVECTOR2(0.0f,0.0f));
	bg_->__texture_id(Texture::TEXTURE_ID_LOGO_BG);
	bg_->SetParameter();


	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SelectBg::Uninitialize(void)
{
	SafeRelease(bg_);
}

//=============================================================================
// update
//=============================================================================
void SelectBg::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void SelectBg::Draw(void)
{
	bg_->Draw();
}

//---------------------------------- EOF --------------------------------------