//*****************************************************************************
//
// option config menu
//
// Author		: Ryotaro Arai
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _OPTION_CONFIG_MENU_H_
#define _OPTION_CONFIG_MENU_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Sprite;

//*****************************************************************************
// class definition
//*****************************************************************************
class OptionConfigMenu : public Basic
{
public:
	enum OPTION_TYPE
	{
		BUTTON_MIN = -1,
		SELECT_BUTTON = 0,
		CANCEL_BUTTON,
		LIGHT_BUTTON,
		JUMP_BUTTON,
		BUTTON_MAX
	};
	// constructor
	OptionConfigMenu(void);

	// destructor
	virtual ~OptionConfigMenu(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// �I��
	void Select(u32 menu);

	const bool __is_select(void)const{ return is_select_;}

	void __is_select(const bool flag){ is_select_ = flag; }

private:
	Sprite* select_button_;
	Sprite* cancel_button_;
	Sprite* light_button_;
	Sprite* jump_button_;

	Sprite* key_1_;
	Sprite* key_2_;
	Sprite* key_3_;
	Sprite* key_4_;
	Sprite* key_5_;
	Sprite* key_6_;

	bool is_select_;
};

#endif	// _OPTION_MENU_H_

//---------------------------------- EOF --------------------------------------
