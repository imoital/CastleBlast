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
		_red=0;
		_green=0;
		_blue=0;
	}
	
	void Sky::draw()
	{
		glDisable(GL_LIGHTING);
		glColor3d(_red, _green, _blue);
		glutSolidSphere(_worldSize, 16, 16);
		glEnable(GL_LIGHTING);
	}

	void Sky::setLevel(int level)
	{
		switch (level) {
		case 1:
			_red=0.53;
			_green=0.81;
			_blue=0.98;
			break;
		case 2:
			_red=0.0;
			_green=0.0;
			_blue=0.0;
			break;
		}
	}

	void Sky::setLevel1(){}
	void Sky::setLevel2(){}
	
	void Sky::update(unsigned long elapsed_millis) {}
}