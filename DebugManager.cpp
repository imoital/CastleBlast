//
//  DebugManager.cpp
//  Project
//
//  Created by Inês on 10/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "DebugManager.h"
#include "DebugMode.h"

namespace CastleBlast {
	
	DebugManager::DebugManager() :cg::Entity("DEBUG_MANAGER") 
	{}
	
	DebugManager::~DebugManager()
	{}
	
	void DebugManager::init()
	{}
	
	void DebugManager::addObjectDebug(DebugMode *debug)
	{
		_debugClasses.push_back(debug);
	}
	
	void DebugManager::toggleDebug()
	{
		for (int i = 0; i < _debugClasses.size(); i++) {
			_debugClasses[i]->toggleDebug();
		}
	}
	
}