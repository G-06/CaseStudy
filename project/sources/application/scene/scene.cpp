//*****************************************************************************
//
// scene
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "scene/scene.h"
#include "scene/factory/scene_factory.h"

//=============================================================================
// constructor
//=============================================================================
Scene::Scene(const TYPE& type)
	:type_(type)
	,next_scene_factory_(nullptr)
	,is_fade_(false)
	,is_stop_(false)
{
}

//=============================================================================
// destructor
//=============================================================================
Scene::~Scene(void)
{
}

//---------------------------------- EOF --------------------------------------
