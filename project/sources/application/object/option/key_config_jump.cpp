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
#include "../option.h"
#include "object/option/option_sprite_smooth.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
// string
const D3DXVECTOR2 DEFAULT_SIZE = Option::DEFAULT_MENU_SIZE;
const D3DXVECTOR2 DEFAULT_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f - 250,525.0f);
// number
const D3DXVECTOR2 DEFAULT_NUM_SIZE = D3DXVECTOR2(75.0f, 75.0f);
const D3DXVECTOR2 DEFAULT_NUM_POSITION = D3DXVECTOR2(DEFAULT_POSITION.x + 300.0f, DEFAULT_POSITION.y);

//=============================================================================
// constructor
//=============================================================================
KeyConfigJump::KeyConfigJump(void)
	:jump_button_(NULL)
	,set_button_number_(NULL)
	,set_button_number_frame_(NULL)
	,current_key_event_(NULL)
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
	jump_button_ = new OptionSpriteSmooth();
	jump_button_->Initialize();
	jump_button_->__size(DEFAULT_SIZE);
	jump_button_->__position(DEFAULT_POSITION);
	jump_button_->__texture_id(Texture::TEXTURE_ID_OPTION_STRING_OP_JUMP);

	set_button_number_ = new OptionSpriteSmooth();
	set_button_number_->Initialize();
	set_button_number_->__size(DEFAULT_NUM_SIZE);
	set_button_number_->__position(DEFAULT_NUM_POSITION);
	set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_01);

	set_button_number_frame_ = new OptionSpriteSmooth();
	set_button_number_frame_->Initialize();
	set_button_number_frame_->__size(DEFAULT_NUM_SIZE);
	set_button_number_frame_->__position(DEFAULT_NUM_POSITION);
	set_button_number_frame_->__texture_id(Texture::TEXTURE_ID_TITLE_SELECT_FRAME_000);

	current_key_event_ = NULL;
	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void KeyConfigJump::Uninitialize(void)
{
	SafeRelease(jump_button_);
	SafeRelease(set_button_number_);
	SafeRelease(set_button_number_frame_);
}

//=============================================================================
// update
//=============================================================================
void KeyConfigJump::Update(void)
{
	jump_button_->Update();
	set_button_number_->Update();
	set_button_number_frame_->Update();
}

//=============================================================================
// draw
//=============================================================================
void KeyConfigJump::Draw(void)
{
	jump_button_->Draw();
	set_button_number_frame_->Update();
	set_button_number_->Draw();
}

//=============================================================================
// select
//=============================================================================
void KeyConfigJump::Select(bool is_select)
{
}

//=============================================================================
// set texture
//=============================================================================
void KeyConfigJump::__set_button_number_texture(INPUT_EVENT button)
{	
	switch(button)
	{
		case INPUT_EVENT_PAD_4:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_04);
			break;

		case INPUT_EVENT_PAD_5:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_05);
			break;

		case INPUT_EVENT_PAD_6:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_06);
			break;

		case INPUT_EVENT_PAD_7:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_07);
			break;

		case INPUT_EVENT_PAD_8:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_08);
			break;

		case INPUT_EVENT_PAD_9:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_09);
			break;

		case INPUT_EVENT_PAD_10:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_10);
			break;

		case INPUT_EVENT_PAD_11:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_11);

			break;

		case INPUT_EVENT_PAD_12:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_12);

			break;

		case INPUT_EVENT_PAD_13:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_13);
			break;

		case INPUT_EVENT_PAD_14:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_OPTION_KEY_14);
			break;

		case INPUT_EVENT_PAD_15:
			set_button_number_->__texture_id(Texture::TEXTURE_ID_NONE);
			break;
	}
}

//=============================================================================
// set alpha
//=============================================================================
void KeyConfigJump::SetAlpha(f32 alpha)
{
	jump_button_->__color(D3DXCOLOR(1,1,1,alpha));
}

//---------------------------------- EOF --------------------------------------
