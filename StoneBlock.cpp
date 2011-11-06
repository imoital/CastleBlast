//
//  StoneBlock.cpp
//  Project
//
//  Created by Inês on 10/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "StoneBlock.h"

namespace CastleBlast {
	
	StoneBlock::StoneBlock() : Block() {
		_materialDL = loadType();
		
		mat_ambient[0] = 0.5f;
		mat_ambient[1] = 0.5f;
		mat_ambient[2] = 0.5f;
		mat_ambient[3] = 1.0f;
		
		mat_difusse[0] = 0.4f;
		mat_difusse[1] = 0.4f;
		mat_difusse[2] = 0.4f;
		mat_difusse[3] = 1.0f;
		
		mat_specular[0] = 0.2f;
		mat_specular[1] = 0.2f;
		mat_specular[2] = 0.2f;
		mat_specular[3] = 1.0f;
		
		shininess = 5;
	}
	
	StoneBlock::~StoneBlock() {}
	
	int StoneBlock::loadType()
	{
#ifdef __APPLE__
		return Loader::loadTexture("Textures/stone.jpg");
#else
		return Loader::loadTexture("..\\..\\src\\Textures\\stone.jpg");
#endif
	}
}