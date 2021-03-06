//*****************************************************************************
//
// assert effect clear
//
// Author		: Kenji Kabutomori
//				: taichi kitazawa
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "assert_effect_clear.h"
#include "render/sprite.h"
#include "object/stage_select/select_record.h"
#include "object/object_newrecord.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 AssertEffectClear::SRIDE_IN_FRAME = 30;
const u32 AssertEffectClear::STOP_FRAME = 60;
const u32 AssertEffectClear::SRIDE_OUT_FRAME = 30;
const u32 AssertEffectClear::RECORD_SRIDE_IN_FRAME = 30;
const u32 AssertEffectClear::NEW_RECORD_SRIDE_IN_FRAME = 30;
const u32 AssertEffectClear::NEW_RECORD_STOP_FRAME = 10;

const f32 CLEAR_SIZE_SCALE = 1.0f;
const D3DXVECTOR2 CLEAR_SIZE = D3DXVECTOR2(1028.0f * CLEAR_SIZE_SCALE, 256.0f * CLEAR_SIZE_SCALE);

const D3DXVECTOR2 AssertEffectClear::CLEAR_START_POSITION	= D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 1.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
const D3DXVECTOR2 AssertEffectClear::CLEAR_STOP_POSITION	= D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
const D3DXVECTOR2 AssertEffectClear::CLEAR_END_POSITION		= D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.35f,DEFAULT_SCREEN_HEIGHT * 0.37f);

const D3DXVECTOR2 AssertEffectClear::RECORD_START_POSITION =		D3DXVECTOR2(DEFAULT_SCREEN_WIDTH - 220.0f,50.0f);
const D3DXVECTOR2 AssertEffectClear::RECORD_END_POSITION =			D3DXVECTOR2(DEFAULT_SCREEN_WIDTH - 220.0f,DEFAULT_SCREEN_HEIGHT * 0.35f);

const D3DXVECTOR2 AssertEffectClear::NEW_RECORD_START_POSITION =	D3DXVECTOR2(DEFAULT_SCREEN_WIDTH + 300.0f,DEFAULT_SCREEN_HEIGHT * 0.51f);
const D3DXVECTOR2 AssertEffectClear::NEW_RECORD_END_POSITION =		D3DXVECTOR2(DEFAULT_SCREEN_WIDTH - 290.0f,DEFAULT_SCREEN_HEIGHT * 0.51f);

const D3DXVECTOR2 SPRITE_SIZE = D3DXVECTOR2(1028.0f,256.0f);
const D3DXVECTOR2 SPRITE_BACK_SIZE = D3DXVECTOR2(1280.0f,450.0f);
const f32 SPRITE_BACK_SIZE_ADD = 20.0f;

//=============================================================================
// constructor
//=============================================================================
AssertEffectClear::AssertEffectClear(void)
	:AssertEffect(TYPE_CLEAR)
	,sprite_(nullptr)
	,sprite_back_(nullptr)
	,position_(0.0f,0.0f)
	,back_position_(0.0f,0.0f)
	,record_position_(RECORD_START_POSITION)
	,new_record_position_(NEW_RECORD_START_POSITION)
	,frame_count_(0)
	,is_stop_(false)
	,time_(0)
	,record_(nullptr)
	,is_first_(true)
	,is_turtrial_(false)
	,back_move_(true)
{
}

//=============================================================================
// destructor
//=============================================================================
AssertEffectClear::~AssertEffectClear(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool AssertEffectClear::Initialize(void)
{
	sprite_ = new Sprite();
	sprite_->Initialize();
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(SPRITE_SIZE);
	sprite_->__texture_id(Texture::TEXTURE_ID_GAME_STRING_CLEAR);
	position_ = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 1.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
	sprite_->SetParameter();

	//record_ = new SelectRecord();
	//record_->Initialize();
	//record_->__set_time(time_);
	//record_->__set_position(record_position_);

	sprite_back_ = new Sprite();
	sprite_back_->Initialize();
	sprite_back_->__point(Sprite::POINT_CENTER);
	sprite_back_->__size(D3DXVECTOR2(SPRITE_BACK_SIZE.x,0.0f));
	sprite_back_->__color(D3DXCOLOR(0.0f,0.0f,0.0f,0.6f));
	sprite_back_->SetParameter();

	new_record_ = new ObjectNewRecord();
	new_record_ ->Initialize();
	new_record_->__set_position(new_record_position_);

	is_assert_ = false;
	new_record_flag_ = false;


	D3DXVECTOR2 position = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 1.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
	D3DXVECTOR2 position_back = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);

	position_ = position;
	back_position_ = position_back;

	sprite_->__position(position_);
	sprite_->SetParameter();
	sprite_back_->__position(back_position_);
	sprite_back_->SetParameter();


	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void AssertEffectClear::Uninitialize(void)
{
	SafeRelease(sprite_);
	SafeRelease(sprite_back_);

	//if(record_ != nullptr)
	//	SafeRelease(record_);

	SafeRelease(new_record_);
}

//=============================================================================
// update
//=============================================================================
void AssertEffectClear::Update(void)
{
	D3DXVECTOR2 vector = D3DXVECTOR2(0.0f,0.0f);

	if(is_assert_)
	{
		if(back_move_)
		{
			D3DXVECTOR2 size = sprite_back_->__size();
			size.y += SPRITE_BACK_SIZE_ADD;
			if(size.y >= SPRITE_BACK_SIZE.y)
			{
				size.y = SPRITE_BACK_SIZE.y;
				back_move_ = false;
			}
			sprite_back_->__size(size);
			sprite_back_->SetParameter();
		}
		else
		{
			frame_count_++;

			if(frame_count_ <= SRIDE_IN_FRAME)
			{
				vector = CLEAR_STOP_POSITION - CLEAR_START_POSITION;
				position_ = CLEAR_START_POSITION + vector * 1.0f / (f32)SRIDE_IN_FRAME * (f32)frame_count_;
//				back_position_ = position_;
			}
			else if(frame_count_ <= SRIDE_IN_FRAME + STOP_FRAME)
			{
			}
			else if(frame_count_ <= SRIDE_IN_FRAME + STOP_FRAME + SRIDE_OUT_FRAME)
			{
				vector = CLEAR_END_POSITION - CLEAR_STOP_POSITION;
				position_ = CLEAR_STOP_POSITION + vector * 1.0f / (f32)SRIDE_OUT_FRAME * (f32)(frame_count_ - SRIDE_IN_FRAME - STOP_FRAME);
				const D3DXVECTOR2 back_position = D3DXVECTOR2(back_position_.x, position_.y);
				back_position_ = back_position;
			}
			else if(frame_count_ <= SRIDE_IN_FRAME + STOP_FRAME + SRIDE_OUT_FRAME + RECORD_SRIDE_IN_FRAME)
			{
				vector = RECORD_END_POSITION - RECORD_START_POSITION;
				record_position_ = RECORD_START_POSITION + vector * 1.0f / (f32)SRIDE_OUT_FRAME * (f32)(frame_count_ - SRIDE_IN_FRAME - STOP_FRAME - SRIDE_OUT_FRAME);
			}
			else if(frame_count_ <= SRIDE_IN_FRAME + STOP_FRAME + SRIDE_OUT_FRAME + RECORD_SRIDE_IN_FRAME+NEW_RECORD_STOP_FRAME)
			{
				//レコードが出たのでニューレコードじゃなかった時はもうシーン遷移してもよい
				if(new_record_flag_ == false)
				{
					is_stop_ = true;
				}
			}
			else if(frame_count_ <= SRIDE_IN_FRAME + STOP_FRAME + SRIDE_OUT_FRAME + RECORD_SRIDE_IN_FRAME+NEW_RECORD_STOP_FRAME+NEW_RECORD_SRIDE_IN_FRAME)
			{
				if(is_first_ && new_record_flag_ == true)
				{
					GET_SE->Play(SE::SE_ID_NEW_RECORD);
				}
				vector = NEW_RECORD_END_POSITION - NEW_RECORD_START_POSITION;
				new_record_position_ = NEW_RECORD_START_POSITION + vector * 1.0f / (f32)SRIDE_OUT_FRAME * (f32)(frame_count_ - SRIDE_IN_FRAME - STOP_FRAME - SRIDE_OUT_FRAME - RECORD_SRIDE_IN_FRAME - NEW_RECORD_STOP_FRAME);
			}
			else
			{
				is_stop_ = true;
			}
		}
	} // assert
}

//=============================================================================
// draw
//=============================================================================
void AssertEffectClear::Draw(void)
{
	if(is_assert_)
	{
//		sprite_back_->__position(back_position_);
		sprite_back_->Draw();

		sprite_->__position(position_);
		sprite_->Draw();

		if(is_turtrial_ == false)
		{
			if(record_ != nullptr)
			{
				record_->__set_position(record_position_);
				record_->Draw();
			}

				if(new_record_flag_ == true)
			{

				new_record_->__set_position(new_record_position_);
				new_record_->Draw();
			}
		}
	}
}

//=============================================================================
// set time
//=============================================================================
void AssertEffectClear::SetTime(u32 time)
{
	if(record_ != nullptr)
	{
		record_->__set_time(time);
		record_->Update();
	}
}

//---------------------------------- EOF --------------------------------------
