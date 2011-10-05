//
//  App.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "App.h"

namespace AVT {
	
	App::App() {
		_windowInfo.caption = "AVT";
		_windowInfo.width = 800;
		_windowInfo.height = 600;
	}
	App::~App() {}
	
	void App::createEntities() {}
	
	void App::createViews() {}
}