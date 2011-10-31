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