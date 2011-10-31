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
		_position = cg::Vector3d(0,1,0);
		_wheelRotation = 0;
		_cannonRotation = 0;
		
		_cannon = new Model();
		_wheels = new Model();
#ifdef __APPLE__
		_cannon->loadModelData("Models/cannon.obj");
		_wheels->loadModelData("Models/wheels.obj");
#else
		_cannon->loadModelData("..\\..\\src\\Models\\cannon.obj");
		_wheel1->loadModelData("..\\..\\src\\Models\\wheels.obj");
#endif

	}
	
	void Cannon::draw()
	{
		glPushMatrix();
		{
			glScaled(2, 2, 2); // if you remove the scale don't forget to remove the GL_NORMALIZE (lines 52 and 54)
			glTranslated(_position[0], _position[1], _position[2]); //translate the whoel cannon (cannon+wheels)
			glPushMatrix(); 
			{
				glTranslatef(.5, 1.7, 0); // translate the wheels to be in the final position
				glRotatef(_wheelRotation, 0, 0, 1); // Rotates the Wheels
				_wheels->drawModel();	//draw the wheels
			}
			glPopMatrix();
		
			glPushMatrix();
			{
				glRotatef(_cannonRotation, 0, 0, 1); // rotates the cannon
				glEnable(GL_NORMALIZE);		// needs to be where because of the scale
				_cannon->drawModel();		// draw the cannon
				glDisable(GL_NORMALIZE);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	
	void Cannon::update(unsigned long elapsed_millis)
	{
		if(cg::KeyBuffer::instance()->isKeyDown('w')) {
			_position[0] = _position[0] + 0.0002*elapsed_millis;
			_wheelRotation = _wheelRotation - 0.01*elapsed_millis;
		}
		if(cg::KeyBuffer::instance()->isKeyDown('s')) {
			_position[0] = _position[0] - 0.0002*elapsed_millis;
			_wheelRotation = _wheelRotation + 0.01*elapsed_millis;
		}
		if(cg::KeyBuffer::instance()->isKeyDown('a')) {
			_cannonRotation = _cannonRotation + 0.01*elapsed_millis;
		}
		if(cg::KeyBuffer::instance()->isKeyDown('d')) {
			_cannonRotation = _cannonRotation - 0.01*elapsed_millis;
		}
		
		//std::cout << "" << _wheelRotation << std::endl;
	}
}