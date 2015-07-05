//*****************************************************************************
//
// key config cancel
//
// Author		: Ryotaro Arai
//				: masato masuda
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _KEY_CONFIG_CANCEL_H_
#define _KEY_CONFIG_CANCEL_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "system/system.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class OptionSpriteSmooth;

//*****************************************************************************
// class definition
//*****************************************************************************
class KeyConfigCancel : public Basic
{
public:
	// constructor
	KeyConfigCancel(void);

	// destructor
	virtual ~KeyConfigCancel(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// draw
	void Draw(void);

	// �I��
	void Select(bool is_select);

	void SetAlpha(f32 alpha);

	void __set_button_number_texture(INPUT_EVENT button);

private:
	OptionSpriteSmooth* cancel_button_;
	OptionSpriteSmooth* cancel_button_frame_;
	OptionSpriteSmooth* set_button_number_;
	OptionSpriteSmooth* set_button_number_frame_;

	u32 current_key_event_;
};

#endif	// _KEY_CONFIG_CANCEL_H_

//---------------------------------- EOF --------------------------------------
