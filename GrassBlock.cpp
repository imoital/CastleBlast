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