//
//  DebugManager.h
//  Project
//
//  Created by Inês on 10/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
//  Class to manage all the classes that implement the class DebugMode

#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <cg/cg.h>

namespace CastleBlast {
	
	class DebugMode; // Need to add this because of the loop in the includes
	
	class DebugManager : public cg::Entity{
	private:
		std::vector<DebugMode*> _debugClasses;
		
	public:
		DebugManager();
		~DebugManager();
		void init();
		
		void addObjectDebug(DebugMode *debug);
		void toggleDebug();
	};
}

#endif