//
//  Lights.h
//  Project
//
//  Created by Inês on 10/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#ifndef LIGHTS_H
#define LIGHTS_H

#include <cg/cg.h>

namespace CastleBlast {
	
	// Lights : class that manages the lights in the scene
	class Lights : public cg::Entity {
		
	public:
		Lights();
		~Lights();
		
		void init();
	};
}

#endif