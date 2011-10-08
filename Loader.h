//
//  Loader.h
//  Project
//
//  Created by Inês on 10/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef LOADER_H
#define LOADER_H

#include "cg/cg.h"

namespace CastleBlast {
	
	// Loader : a classes that loads textures to be compatible with OpenGL 
	class Loader {
	public:
		static GLuint loadTexture(const char *filename);
	};
}

#endif