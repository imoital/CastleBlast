//
//  Sky.cpp
//  Project
//
//  Created by Inês on 10/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Sky.h"

namespace CastleBlast {
	
	Sky::Sky() : cg::Entity("SKY") {}
	
	Sky::~Sky() {}
	
	void Sky::init()
	{
		_worldSize = cg::Properties::instance()->getInt("WORLD_SIZE");
	}
	
	void Sky::draw()
	{
		glDisable(GL_LIGHTING);
		glColor3d(0.53, 0.81, 0.98);
		glutSolidSphere(_worldSize, 16, 16);
		glEnable(GL_LIGHTING);
	}
}