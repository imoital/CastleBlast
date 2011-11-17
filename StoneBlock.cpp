//
//  StoneBlock.cpp
//  Project
//
//  Created by Inês on 10/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "StoneBlock.h"

namespace CastleBlast {
	
	StoneBlock::StoneBlock(cg::Vector3d startFrom) : Block(startFrom) {
		
		topBottom_mat_ambient[0] = 0.5f;
		topBottom_mat_ambient[1] = 0.5f;
		topBottom_mat_ambient[2] = 0.5f;
		topBottom_mat_ambient[3] = 1.0f;
		
		topBottom_mat_difusse[0] = 0.4f;
		topBottom_mat_difusse[1] = 0.4f;
		topBottom_mat_difusse[2] = 0.4f;
		topBottom_mat_difusse[3] = 1.0f;
		
		topBottom_mat_specular[0] = 0.2f;
		topBottom_mat_specular[1] = 0.2f;
		topBottom_mat_specular[2] = 0.2f;
		topBottom_mat_specular[3] = 1.0f;
		
		topBottom_shininess = 5;
		
		side_mat_ambient[0] = 0.5f;
		side_mat_ambient[1] = 0.5f;
		side_mat_ambient[2] = 0.5f;
		side_mat_ambient[3] = 1.0f;
		
		side_mat_difusse[0] = 0.4f;
		side_mat_difusse[1] = 0.4f;
		side_mat_difusse[2] = 0.4f;
		side_mat_difusse[3] = 1.0f;
		
		side_mat_specular[0] = 0.2f;
		side_mat_specular[1] = 0.2f;
		side_mat_specular[2] = 0.2f;
		side_mat_specular[3] = 1.0f;
		
		side_shininess = 5;
		
		loadTextures();
	}
	
	StoneBlock::~StoneBlock() {}
	
	void StoneBlock::loadTextures()
	{
#ifdef __APPLE__
		_topBottomTexture = Loader::loadTexture("Textures/stone.png");
#else
		_topBottomTexture = Loader::loadTexture("..\\..\\src\\Textures\\stone.png");
#endif
		_sideTexture = _topBottomTexture;
	}
}