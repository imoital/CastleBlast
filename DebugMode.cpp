//
//  DebugMode.cpp
//  Project
//
//  Created by Inês on 10/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "DebugMode.h"

namespace CastleBlast {
	
	DebugMode::DebugMode () 
	{
		DebugManager *debugManager = (DebugManager*)cg::Registry::instance()->get("DEBUG_MANAGER");
		debugManager->addObjectDebug(this);
	}
	
	DebugMode::~DebugMode()
	{}
}
