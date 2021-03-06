//*****************************************************************************
//
// direct input
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include gaurd
//*****************************************************************************
#pragma once
#ifndef _DIRECT_INPUT_H_
#define _DIRECT_INPUT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"
#include "input_alias.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
class DIDevice;
class Window;
class InputEventBuffer;
class DIVirtual;
class DIKeyboard;
class DIMouse;
class DIPad;

//*****************************************************************************
// class definition
//*****************************************************************************
class DirectInput : public Basic
{
public:
	// constructor
	DirectInput(void);

	// destructor
	virtual ~DirectInput(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// update
	void Update(void);

	// reset device
	void ResetDevice(void);

	// check press
	bool CheckPress(const INPUT_EVENT& input_event);

	// check trigger
	bool CheckTrigger(const INPUT_EVENT& input_event);

	// check release
	bool CheckRelease(const INPUT_EVENT& input_event);

	// check repeat
	bool CheckRepeat(const INPUT_EVENT& input_event);

	// get value
	s32 GetValue(const INPUT_EVENT_VALUE& input_event_value);

	// get press
	INPUT_EVENT GetPress(const INPUT_EVENT& begin_input_event,const INPUT_EVENT& end_input_event);
	INPUT_EVENT GetTrigger(const INPUT_EVENT& begin_input_event,const INPUT_EVENT& end_input_event);

	// register input event vertual
	bool RegisterInputEventVertual(const INPUT_EVENT& input_event_virtual,const INPUT_EVENT& input_event);

	void UnregisterInputEventVertual(const INPUT_EVENT& input_event_virtual,const INPUT_EVENT& input_event);

	// save input event vertual
	void SaveInputEventVertual(void);

private:
	static const s8* SYSTEM_FILE_NAME;
	LPDIRECTINPUT8 direct_input_;
	std::list<DIDevice*> device_list_;
	Window* window_;
	InputEventBuffer* input_event_buffer_;
	DIKeyboard* di_keyboard_;
	DIMouse* di_mouse_;
	DIPad* di_pad_;
	DIVirtual* di_virtual_;
	bool is_use_;
};

#endif // _DIRECT_INPUT_H_

//-----------------------------------EOF---------------------------------------
