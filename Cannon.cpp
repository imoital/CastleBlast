//
//  Cannon.cpp
//  Project
//
//  Created by Inês on 10/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Cannon.h"

namespace CastleBlast {
	
	Cannon::Cannon() :cg::Entity("CANNON") {}
	
	Cannon::~Cannon() {}
	
	void Cannon::init()
	{
		_cannon = new Model();
#ifdef __APPLE__
		_cannon->loadModelData("Models/cannon.obj");
#else
		_cannon->loadModelData("..\\..\\src\\Models\\cannon.obj");
#endif
		
		_wheels = new Model();
#ifdef __APPLE__
		_wheels->loadModelData("Models/wheels.obj");
#else
		_wheel1->loadModelData("..\\..\\src\\Models\\wheels.obj");
#endif
	}
	
	void Cannon::draw()
	{
		cg::Vector3d pos = cg::Vector3d(3,0,0);
		
		glPushMatrix();
			glTranslatef(pos[0], pos[1], pos[2]);
			glScaled(2, 2, 2);
			_wheels->drawModel();
			_cannon->drawModel();
		glPopMatrix();
	}
}