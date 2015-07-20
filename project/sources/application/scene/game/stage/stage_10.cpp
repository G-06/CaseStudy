//*****************************************************************************
//
// stage 10
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "stage_10.h"
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
StageTen::StageTen(void)
	:NormalStage(TYPE_STAGE10)
{
}

//=============================================================================
// destructor
//=============================================================================
StageTen::~StageTen(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageTen::Initialize(void)
{
	GET_BGM->Play(BGM::BGM_ID_CREDIT);
	NormalStage::Initialize();

	map_ = new Map();

	if(!SafeInitialize(map_))
	{
		return false;
	}

	//スタッフロール
	map_->LoadFromFile("data/map/Ending.bin");

	stage_offset_->__stage_size(map_->__size());

	LoadFromFile("data/script/Ending.csv");

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageTen::Uninitialize(void)
{
	NormalStage::Uninitialize();
}

//=============================================================================
// update
//=============================================================================
void StageTen::Update(void)
{
	NormalStage::Update();
}

//=============================================================================
// draw
//=============================================================================
void StageTen::Draw(void)
{
	NormalStage::Draw();
}

//=============================================================================
// create factory
//=============================================================================
StageFactory* StageTen::CreateFactory(void)const
{
	return new StageTenFactory();
}

//---------------------------------- EOF --------------------------------------
