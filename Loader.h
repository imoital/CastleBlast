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
#include "FreeImage.h"

namespace CastleBlast {
	
	// Loader : a classes that loads textures to be compatible with OpenGL 
	class Loader {
	public:
		static GLuint loadTexture(const char *filename);
		static GLuint loadTextureAlpha(const char* filename);
		static std::vector<std::vector<int> > createHeightMap (const char* filename, int maxHeight);
		static GLuint buildFont(GLuint fontTexture);
		static void killFont(GLuint base);
		static GLvoid printFont(GLint x, GLint y, float size, const char *string, int set, GLuint fontTexture, GLuint base);
	};
}

#endif