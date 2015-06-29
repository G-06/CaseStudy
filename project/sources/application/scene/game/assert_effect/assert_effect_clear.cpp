//*****************************************************************************
//
// assert effect clear
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "assert_effect_clear.h"
#include "render/sprite.h"
#include "object/stage_select/select_record.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 AssertEffectClear::SRIDE_IN_FRAME = 30;
const u32 AssertEffectClear::STOP_FRAME = 60;
const u32 AssertEffectClear::SRIDE_OUT_FRAME = 30;
const u32 AssertEffectClear::RECORD_SRIDE_IN_FRAME = 30;

const D3DXVECTOR2 AssertEffectClear::CLEAR_START_POSITION	= D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 1.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
const D3DXVECTOR2 AssertEffectClear::CLEAR_STOP_POSITION	= D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
const D3DXVECTOR2 AssertEffectClear::CLEAR_END_POSITION		= D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.3f);

const D3DXVECTOR2 AssertEffectClear::RECORD_START_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 1.5f);
const D3DXVECTOR2 AssertEffectClear::RECORD_END_POSITION = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);

//=============================================================================
// constructor
//=============================================================================
AssertEffectClear::AssertEffectClear(void)
	:AssertEffect(TYPE_CLEAR)
	,sprite_(nullptr)
	,position_(0.0f,0.0f)
	,record_position_(RECORD_START_POSITION)
	,frame_count_(0)
	,is_stop_(false)
	,time_(0)
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
	sprite_->__size(D3DXVECTOR2((f32)DEFAULT_SCREEN_WIDTH,200.0f));
	position_ = D3DXVECTOR2(DEFAULT_SCREEN_WIDTH * 1.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);
	sprite_->SetParameter();

	record_ = new SelectRecord();
	record_->Initialize();
	record_->__set_time(time_);
	record_->__set_position(record_position_);

	is_assert_ = false;

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void AssertEffectClear::Uninitialize(void)
{
	SafeRelease(sprite_);

	SafeRelease(record_);
}

//=============================================================================
// update
//=============================================================================
void AssertEffectClear::Update(void)
{
	D3DXVECTOR2 vector;

	if(is_assert_)
	{
		frame_count_++;

		if(frame_count_ <= SRIDE_IN_FRAME)
		{
			vector = CLEAR_STOP_POSITION - CLEAR_START_POSITION;
			position_ = CLEAR_START_POSITION + vector * 1.0f / (f32)SRIDE_IN_FRAME * (f32)frame_count_;
		}
		else if(frame_count_ <= SRIDE_IN_FRAME + STOP_FRAME)
		{
		}
		else if(frame_count_ <= SRIDE_IN_FRAME + STOP_FRAME + SRIDE_OUT_FRAME)
		{
			vector = CLEAR_END_POSITION - CLEAR_STOP_POSITION;
			position_ = CLEAR_STOP_POSITION + vector * 1.0f / (f32)SRIDE_OUT_FRAME * (f32)(frame_count_ - SRIDE_IN_FRAME - STOP_FRAME);
		}
		else if(frame_count_ <= SRIDE_IN_FRAME + STOP_FRAME + SRIDE_OUT_FRAME + RECORD_SRIDE_IN_FRAME)
		{
			vector = RECORD_END_POSITION - RECORD_START_POSITION;
			record_position_ = RECORD_START_POSITION + vector * 1.0f / (f32)SRIDE_OUT_FRAME * (f32)(frame_count_ - SRIDE_IN_FRAME - STOP_FRAME - SRIDE_OUT_FRAME);
		}
		else
		{
			is_stop_ = true;
		}
	}
}

//=============================================================================
// draw
//=============================================================================
void AssertEffectClear::Draw(void)
{
	if(is_assert_)
	{
		sprite_->__position(position_);
		sprite_->Draw();

		record_->__set_position(record_position_);
		record_->Draw();
	}
}

//=============================================================================
// set time
//=============================================================================
void AssertEffectClear::SetTime(u32 time)
{
	record_->__set_time(time);
	record_->Update();
}

//---------------------------------- EOF --------------------------------------