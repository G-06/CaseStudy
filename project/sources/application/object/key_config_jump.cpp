//*****************************************************************************
//
// key config jump
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "key_config_jump.h"
#include "render/sprite.h"
#include "system/system.h"
#include "option.h"

//=============================================================================
// constructor
//=============================================================================
KeyConfigJump::KeyConfigJump(void)
{
}

//=============================================================================
// destructor
//=============================================================================
KeyConfigJump::~KeyConfigJump(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool KeyConfigJump::Initialize(void)
{
	jump_button_ = new Sprite();
	jump_button_->Initialize();
	jump_button_->__size(Option::DEFAULT_MENU_SIZE);
	jump_button_->__position(D3DXVECTOR2((f32)GET_SYSTEM.__window()->__width()/2 - 250,525.0f));
	jump_button_->__texture_id(Texture::TEXTURE_ID_JUMP_BUTTON);
	jump_button_->__point(Sprite::POINT_CENTER);
	jump_button_->SetParameter();

	current_key_event_ = NULL;
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyConfigJump::Uninitialize(void)
{
	SafeRelease(jump_button_);
}

//=============================================================================
// update
//=============================================================================
void KeyConfigJump::Update(void)
{
}

//=============================================================================
// draw
//=============================================================================
void KeyConfigJump::Draw(void)
{
	jump_button_->Draw();
}

//=============================================================================
// select
//=============================================================================
void KeyConfigJump::Select(bool is_select)
{
	if(is_select == true)
	{
		jump_button_->__size(Option::EXPAND_MENU_SIZE);
	}
	else
	{
		jump_button_->__size(Option::DEFAULT_MENU_SIZE);
	}
	
	jump_button_->SetParameter();
}

//---------------------------------- EOF --------------------------------------