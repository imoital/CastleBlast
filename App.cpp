//
//  App.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "App.h"
#include "Lights.h"
//#include "Sky.h"
#include "Fog.h"
#include "Controller.h"
#include "DebugManager.h"
#include "GameManager.h"
#include "ModelManager.h"
#include "FontsManager.h"
#include "CollisionManager.h"

namespace CastleBlast {
	
#ifdef __APPLE__
	App::App() : cg::Application("config.ini")
#else
	App::App() : cg::Application("..\\..\\src\\config.ini")
#endif
	{
		_windowInfo.caption = "Castle Blast";
		_windowInfo.width = 800;
		_windowInfo.height = 600;
	}
	App::~App() {}
	
	void App::createEntities() 
	{
		addEntity(new CollisionManager());
		addEntity(new FontsManager());
		addEntity(new ModelManager());
		addEntity(new DebugManager());
		addEntity(new Controller());
	//	addEntity(new Fog());
		//addEntity(new Sky());
		addEntity(new GameManager());
		//addEntity(new Lights());
	}
	
	void App::createViews() 
	{
		cg::View* v0 = createView("view1");
		v0->linkEntityAtEnd("COLLISION_MANAGER");
		v0->linkEntityAtEnd("CAMERA_MANAGER");
		v0->linkEntityAtEnd("SCENE_MANAGER");
		v0->linkEntityAtEnd("GAME_MANAGER");
		//v0->linkEntityAtEnd("LIGHTS");
		//v0->linkEntityAtEnd("SKY");
	//	v0->linkEntityAtEnd("FOG");
		
	}
}