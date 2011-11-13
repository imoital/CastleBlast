//
//  GrassBlock.h
//  Project
//
//  Created by Inês on 10/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GRASS_BLOCK_H
#define GRASS_BLOCK_H

#include "Block.h"
#include "Loader.h"

namespace CastleBlast {
	
	// GrassBlock : a block whit a grass texture
	class GrassBlock : public Block {
	
	public:
		GrassBlock(cg::Vector3d startFrom);
		~GrassBlock();
		
		void loadTextures();
		
	};
}

#endif