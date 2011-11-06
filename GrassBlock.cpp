//
//  GrassBlock.cpp
//  Project
//
//  Created by Inês on 10/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GrassBlock.h"

namespace CastleBlast {
	
	GrassBlock::GrassBlock() : Block() {
		_materialDL = loadType();
		
		mat_ambient[0] = 0.1f;
		mat_ambient[1] = 0.6f;
		mat_ambient[2] = 0.1f;
		mat_ambient[3] = 1.0f;
		
		mat_difusse[0] = 0.0f;
		mat_difusse[1] = 0.3f;
		mat_difusse[2] = 0.0f;
		mat_difusse[3] = 1.0f;
		
		mat_specular[0] = 0.0f;
		mat_specular[1] = 0.7f;
		mat_specular[2] = 0.0f;
		mat_specular[3] = 1.0f;
		
		shininess = 5;
	}
	
	GrassBlock::~GrassBlock() {}
	
	int GrassBlock::loadType()
	{
#ifdef __APPLE__
		return Loader::loadTexture("Textures/grass.jpg");
#else
		return Loader::loadTexture("..\\..\\src\\Textures\\grass.jpg");
#endif
	}
}