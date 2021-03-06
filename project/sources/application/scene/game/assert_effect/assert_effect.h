//*****************************************************************************
//
// assert effect
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _ASSERT_EFFECT_H_
#define _ASSERT_EFFECT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "basic/basic.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
class AssertEffect : public Basic
{
public:
	enum TYPE
	{
		TYPE_START = 0,
		TYPE_CLEAR,
		TYPE_MAX,
	};

	// constructor
	AssertEffect(TYPE type);

	// destructor
	virtual ~AssertEffect(void);

	// initialize
	virtual bool Initialize(void);

	// uninitialize
	virtual void Uninitialize(void);

	// update
	virtual void Update(void);

	// draw
	virtual void Draw(void);

	// accessor
	TYPE __type(void)const { return type_; }
	bool __is_assert(void) { return is_assert_; }
	void __is_assert(bool is_assert) { is_assert_ = is_assert; }

protected:
	TYPE type_;
	bool is_assert_;

};

#endif	// _ASSERT_EFFECT_H_

//---------------------------------- EOF --------------------------------------
