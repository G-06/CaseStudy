//*****************************************************************************
//
// stage 2
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "stage_02.h"
#include "stage_factory.h"
#include "object/map.h"
#include "object/stage_offset.h"
#include "system/system.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
StageTwo::StageTwo(void)
	:NormalStage(TYPE_STAGE2)
{
}

//=============================================================================
// destructor
//=============================================================================
StageTwo::~StageTwo(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageTwo::Initialize(void)
{
//	GET_BGM->Play(BGM::BGM_ID_STAGE_02);
	NormalStage::Initialize();

	map_ = new Map();

	if(!SafeInitialize(map_))
	{
		return false;
	}

	//ヒカリストリート
	map_->LoadFromFile("data/map/Hikari_street.bin");

	stage_offset_->__stage_size(map_->__size());

	LoadFromFile("data/script/Hikari_street.csv");

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageTwo::Uninitialize(void)
{
	NormalStage::Uninitialize();
}

//=============================================================================
// update
//=============================================================================
void StageTwo::Update(void)
{
	NormalStage::Update();
}

//=============================================================================
// draw
//=============================================================================
void StageTwo::Draw(void)
{
	NormalStage::Draw();
}

//=============================================================================
// create factory
//=============================================================================
StageFactory* StageTwo::CreateFactory(void)const
{
	return new StageTwoFactory();
}

//---------------------------------- EOF --------------------------------------
