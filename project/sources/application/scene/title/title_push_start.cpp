//*****************************************************************************
//
// title push_start
//
// Author	: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "title_push_start.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 TitlePushStart::DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f, 450.0f + 100.0f);
const D3DXVECTOR2 TitlePushStart::DEFAULT_SIZE = D3DXVECTOR2(324.0f, 71.0f);
const f32 DEFAULT_ALPHA_SPEED = -0.03f;

//=============================================================================
// constructor
//=============================================================================
TitlePushStart::TitlePushStart(void)
	:sprite_(nullptr)
	,alpha_speed_(DEFAULT_ALPHA_SPEED)
	,alpha_(2.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
TitlePushStart::~TitlePushStart(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool TitlePushStart::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__size(DEFAULT_SIZE);
	sprite_->__position(DEFAULT_POSITION);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__texture_id(Texture::TEXTURE_ID_TITLE_STRING_TEST_A);
	sprite_->SetParameter();
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void TitlePushStart::Uninitialize(void)
{
	SafeRelease(sprite_);
}

//=============================================================================
// update
//=============================================================================
void TitlePushStart::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void TitlePushStart::Draw(void)
{
	sprite_->Draw();
}

//=============================================================================
// __color
//=============================================================================
void TitlePushStart::__color(const D3DXCOLOR& color)
{
	sprite_->__color(color);
	sprite_->SetParameter();
}

//=============================================================================
// __color
//=============================================================================
const D3DXCOLOR TitlePushStart::__color(void)
{
	return (D3DXCOLOR)sprite_->__color();
}

//=============================================================================
// ResetAlphaSpeed
//=============================================================================
void TitlePushStart::ResetAlphaSpeed(void)
{
	alpha_speed_ = DEFAULT_ALPHA_SPEED;
}

//=============================================================================
// __texture_id
//=============================================================================
void TitlePushStart::__texture_id(const Texture::TEXTURE_ID& texture_id)
{
	sprite_->__texture_id(texture_id);
	sprite_->SetParameter();
}

//---------------------------------- EOF --------------------------------------