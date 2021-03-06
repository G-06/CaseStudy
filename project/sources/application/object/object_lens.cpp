//*****************************************************************************
//
// object lens
//
// Author		: Haruki Saito
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "object_lens.h"
#include "render/sprite.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************
const D3DXVECTOR2 ObjectLens::SIZE	= D3DXVECTOR2(128.0f,128.0f);
const u32 ObjectLens::DIVISION_WIDTH	= 1;
const u32 ObjectLens::DIVISION_HEIGHT	= 1;

//=============================================================================
// constructor
//=============================================================================
ObjectLens::ObjectLens(void)
	:object_lens_(nullptr)
	,position_(0.0f,0.0f)
	,rotation_(0.0f)
	,size_(0.0f,0.0f)
{
}

//=============================================================================
// destructor
//=============================================================================
ObjectLens::~ObjectLens(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool ObjectLens::Initialize(void)
{
	object_lens_ = new Sprite();
	object_lens_->Initialize();
	object_lens_->__point(Sprite::POINT_CENTER);
	object_lens_->__division_width(DIVISION_WIDTH);
	object_lens_->__division_height(DIVISION_HEIGHT);
	object_lens_->__size(SIZE);
	object_lens_->__texture_id(Texture::TEXTURE_ID_LENS);
	object_lens_->SetParameter();

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void ObjectLens::Uninitialize(void)
{
	SafeRelease(object_lens_);
}

//=============================================================================
// update
//=============================================================================
void ObjectLens::Update(void)
{
	
}

//=============================================================================
// draw
//=============================================================================
void ObjectLens::Draw(void)
{
	object_lens_->__position(position_);
	object_lens_->__rotation(rotation_);
	object_lens_->Draw();
}



//---------------------------------- EOF --------------------------------------
