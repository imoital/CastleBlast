//
//  App.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "App.h"

namespace CastleBlast {
	
	// TODO: cg::Aplication("config.ini") needs to be windows compatible
	App::App() : cg::Application("config.ini") {
		_windowInfo.caption = "Castle Blast";
		_windowInfo.width = 800;
		_windowInfo.height = 600;
	}
	App::~App() {}
	
	void App::createEntities() 
	{
		addEntity(new Camera());
		addEntity(new Sky());
		addEntity(new SceneManager());
		addEntity(new Lights());
	}
	
	void App::createViews() 
	{
		cg::View* v0 = createView("view1");
		v0->linkEntityAtEnd("CAMERA");
		v0->linkEntityAtEnd("SCENE_MANAGER");
		v0->linkEntityAtEnd("LIGHTS");
		v0->linkEntityAtEnd("SKY");
	}
}