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
#include "stage_07.h"
#include "stage_factory.h"
#include "object/map.h"
#include "object/stage_offset.h"

//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
StageSeven::StageSeven(void)
	:NormalStage(TYPE_TUTORIAL)
{
}

//=============================================================================
// destructor
//=============================================================================
StageSeven::~StageSeven(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool StageSeven::Initialize(void)
{
	NormalStage::Initialize();

	map_ = new Map();

	if(!SafeInitialize(map_))
	{
		return false;
	}

	map_->LoadFromFile("data/map/stage1.bin");

	stage_offset_->__stage_size(map_->__size());

	LoadFromFile("data/script/stage1.csv");

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void StageSeven::Uninitialize(void)
{
	NormalStage::Uninitialize();
}

//=============================================================================
// update
//=============================================================================
void StageSeven::Update(void)
{
	NormalStage::Update();
}

//=============================================================================
// draw
//=============================================================================
void StageSeven::Draw(void)
{
	NormalStage::Draw();
}

//=============================================================================
// create factory
//=============================================================================
StageFactory* StageSeven::CreateFactory(void)const
{
	return new StageSevenFactory();
}

//---------------------------------- EOF --------------------------------------