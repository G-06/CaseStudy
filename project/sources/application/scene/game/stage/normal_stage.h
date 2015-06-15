//*****************************************************************************
//
// stage
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _NORMAL_STAGE_H_
#define _NORMAL_STAGE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "stage.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class GamePlayer;
class Map;
class StageOffset;
class Gimmick;

//*****************************************************************************
// class definition
//*****************************************************************************
class NormalStage : public Stage
{
public:
	// constructor
	NormalStage(const TYPE& type);

	// destructor
	virtual ~NormalStage(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// update
	virtual void Update(void);

	// draw
	virtual void Draw(void);

	// create factory
	virtual StageFactory* CreateFactory(void)const = 0;

	// load from file
	bool LoadFromFile(const s8* filename);

	// load from memory
	bool LoadFromMemory(const s8* data);

	u32 FindWord(s8* dest,const s8* source,s8* words);

	// accessor

protected:
	GamePlayer* game_player_;
	Map* map_;
	StageOffset* stage_offset_;
	std::list<Gimmick*> gimmick_container_;
	u32 time_count_;
};

#endif	// _NORMAL_STAGE_H_

//---------------------------------- EOF --------------------------------------
