//
//  DebugMode.h
//  Project
//
//  Created by Inês on 10/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef DEBUG_MODE_H
#define DEBUG_MODE_H

#include "DebugManager.h"

#define ON true
#define OFF false

namespace CastleBlast {
	class DebugMode {
	public:
		DebugMode();
		~DebugMode();
		
		virtual void toggleDebug() = 0;
	};
}

#endif