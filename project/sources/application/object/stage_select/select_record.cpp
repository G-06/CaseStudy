//*****************************************************************************
//
// stage select bg
//
// Author		: taichi kitazawa
//
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "select_record.h"
#include "select_number.h"
#include "render/sprite.h"
#include "system/system.h"

const u32 NUMBER_SIZE_X = 50;	//数字1つの横幅
const f32 DEFAULT_POSX = 400;	//左端の数字のX
const f32 DEFAULT_POSY = 500;	//左端の数字のY


//=============================================================================
// constructor
//=============================================================================
SelectRecord::SelectRecord(void)
{
}

//=============================================================================
// destructor
//=============================================================================
SelectRecord::~SelectRecord(void)
{
}

//=============================================================================
// initialize
//=============================================================================
bool SelectRecord::Initialize(void)
{
	//
	for(int i=0;i<4;i++)
	{
		number_[i] = new Number();
		number_[i] -> Initialize();
		number_[i] ->__Set_position(D3DXVECTOR2((f32)NUMBER_SIZE_X*i+DEFAULT_POSX,DEFAULT_POSY));
	}
	offset_position_ = D3DXVECTOR2(0,0);
	time_ =0;
	__set_time(time_);

	return true;
}

//=============================================================================
// uninitialize
//=============================================================================
void SelectRecord::Uninitialize(void)
{
	for(int i=0;i<4;i++)
	{
		SafeRelease(number_[i]);
	}
}

//=============================================================================
// update
//=============================================================================
void SelectRecord::Update(void)
{
	for(int i=0;i<4;i++)
	{
		number_[i] ->__Set_position(D3DXVECTOR2(50*i+400 + offset_position_.x,500));
		number_[i]->Update();
	}
}

//=============================================================================
// draw
//=============================================================================
void SelectRecord::Draw(void)
{
	for(int i=0;i<4;i++)
	{
		number_[i]->Draw();
	}

}


void SelectRecord::__set_time(u32 time)
{

	time_=time;
	//
	u32 workA=0;
	f32 workB=0;

	u32 min=0;
	u32 sec=0;

	workA = time_;

	//秒を割り出す
	sec = workA%60;
	//秒を引いて分のみにする
	workA-=sec;
	//ふんを割り出す
	min=workA/60;


	workA = min;
	//分　１０の位
	workB = (f32)(workA%10);
	number_[1]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//分　１の位
	workB = (f32)(workA%10);
	number_[0]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	workA = sec;
	//秒　１０の位
	workB = (f32)(workA%10);
	number_[3]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

	//秒　１の位
	workB = (f32)(workA%10);
	number_[2]->__Set_index((u32)workB);
	workA -= (u32)workB;
	workA /= 10;

}

//---------------------------------- EOF --------------------------------------
