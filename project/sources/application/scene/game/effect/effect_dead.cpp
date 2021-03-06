//*****************************************************************************
//
// effect dead
//
// Author		: Ryotaro Arai
//				: Taichi Kitazawa
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "effect_dead.h"
#include "render/sprite.h"

static const u32 PLAY_TIME = 45;

//*****************************************************************************
// constant definition
//*****************************************************************************
const Animation::DATA EffectDead::DEAD_EFFECT[EffectDead::DEAD_EFFECT_PATTERN] =
{
	Animation::DATA(4,1,0),
	Animation::DATA(4,2,1),
	Animation::DATA(4,3,2),
	Animation::DATA(4,4,3),
	Animation::DATA(4,5,4),
	Animation::DATA(4,6,5),
	Animation::DATA(4,7,6),
	Animation::DATA(4,0,7)
};


//=============================================================================
// constructor
//=============================================================================
EffectDead::EffectDead(void)
	:Effect(TYPE_NYAS_DEAD)
	,sprite_(nullptr)
	,frame_count_(0)
{
}

//=============================================================================
// destructor
//=============================================================================
EffectDead::~EffectDead(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool EffectDead::Initialize(void)
{
	animation_ = new Animation();
	animation_->Add(&DEAD_EFFECT[0], sizeof(Animation::DATA)*EffectDead::DEAD_EFFECT_PATTERN);
	animation_->Start(0);

	sprite_ = new Sprite();
	SafeInitialize(sprite_);
	sprite_->__point(Sprite::POINT_CENTER);
	sprite_->__size(D3DXVECTOR2(256.0f,256.0f));
	sprite_->__texture_id(Texture::TEXTURE_ID_EFFECT_NYAS_DEAD);
	sprite_->__division_width(EffectDead::DEAD_EFFECT_PATTERN);
	sprite_->__index(0);
	sprite_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void EffectDead::Uninitialize(void)
{
	SafeRelease(sprite_);
	SafeRelease(animation_);
}

//=============================================================================
// update
//=============================================================================
void EffectDead::Update(void)
{
	frame_count_++;

	if(frame_count_ > PLAY_TIME)	//死ぬエフェクトの再生が終わり
	{
		is_death_ = true;
	}

	animation_->Update();
	sprite_->__index(animation_->__current_index());
	sprite_->SetParameter();
}

//=============================================================================
// draw
//=============================================================================
void EffectDead::Draw(void)
{
	sprite_->__position(position_ - offset_position_);
	sprite_->Draw();
}

//---------------------------------- EOF --------------------------------------
