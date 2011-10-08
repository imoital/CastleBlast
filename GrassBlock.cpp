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
		return Loader::loadTexture("Textures/grass.jpg"); //TODO: windows compatible
	}
}