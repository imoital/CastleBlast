//
//  StoneBlock.h
//  Project
//
//  Created by Inês on 10/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef STONE_BLOCK_H
#define STONE_BLOCK_H

#include "Loader.h"
#include "Block.h"

namespace CastleBlast {
	
	// StoneBlock : a block whit a stone texture
	class StoneBlock : public Block {
		
	public:
		StoneBlock();
		~StoneBlock();
		
		void loadTextures();
		
	};
}

#endif