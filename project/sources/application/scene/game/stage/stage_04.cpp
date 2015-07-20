//*****************************************************************************
//
// stage 1
//
// Author		: kitazawa taichi
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "stage_04.h"
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
StageFour::StageFour(void)
	:NormalStage(TYPE_STAGE4)
{
}

//=============================================================================
// destructor
//=============================================================================
StageFour::~StageFour(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageFour::Initialize(void)
{
	GET_BGM->Play(BGM::BGM_ID_STAGE_04);
	NormalStage::Initialize();

	map_ = new Map();

	if(!SafeInitialize(map_))
	{
		return false;
	}

	map_->LoadFromFile("data/work/otiru.bin");

	stage_offset_->__stage_size(map_->__size());

	LoadFromFile("data/work/otiru.csv");

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageFour::Uninitialize(void)
{
	NormalStage::Uninitialize();
}

//=============================================================================
// update
//=============================================================================
void StageFour::Update(void)
{
	NormalStage::Update();
}

//=============================================================================
// draw
//=============================================================================
void StageFour::Draw(void)
{
	NormalStage::Draw();
}

//=============================================================================
// create factory
//=============================================================================
StageFactory* StageFour::CreateFactory(void)const
{
	return new StageFourFactory();
}

//---------------------------------- EOF --------------------------------------
