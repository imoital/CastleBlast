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
		
		_wheel1 = new Model();
#ifdef __APPLE__
		_wheel1->loadModelData("Models/wheel.obj");
#else
		_wheel1->loadModelData("..\\..\\src\\Models\\cannon.obj");
#endif
		
		_wheel2 = new Model();
#ifdef __APPLE__
		_wheel2->loadModelData("Models/wheel.obj");
#else
		_wheel2->loadModelData("..\\..\\src\\Models\\cannon.obj");
#endif
	}
	
	void Cannon::draw()
	{
		cg::Vector3d pos = cg::Vector3d(3,2.7,0);
		
		glPushMatrix();
			glTranslatef(pos[0]-2, pos[1]-0.5, pos[2]+2.5);
			glRotatef(-90, 0, 1, 0);
			_wheel1->drawModel();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(pos[0]-2, pos[1]-0.5, pos[2]-2.5);
			glRotatef(90, 0, 1, 0);
			_wheel1->drawModel();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(pos[0], pos[1], pos[2]);
			glScaled(2, 2, 2);
			glRotatef(75, 0, 0, 1);
			_cannon->drawModel();
		glPopMatrix();
	}
}