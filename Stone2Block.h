//
//  StoneBlock2.h
//  Project
//
//  Created by Inês on 10/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef STONEE_BLOCK_H
#define STONEE_BLOCK_H

#include "Loader.h"
#include "Block.h"

namespace CastleBlast {
	
	// StoneBlock : a block whit a stone texture
	class Stone2Block : public Block {
		
	public:
		Stone2Block(cg::Vector3d startFrom);
		~Stone2Block();
		
		void loadTextures();
		
	};
}

#endif