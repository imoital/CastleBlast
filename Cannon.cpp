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
		_position = cg::Vector3d(0,0,0);
		_wheelRotation = 0;
		_cannonRotation = 0;
		
		_cannon = new Model();
		_wheels = new Model();
#ifdef __APPLE__
		_cannon->loadModelData("Models/cannon.obj");
		_wheels->loadModelData("Models/wheels.obj");
#else
		_cannon->loadModelData("..\\..\\src\\Models\\cannon.obj");
		_wheels->loadModelData("..\\..\\src\\Models\\wheels.obj");
#endif

	}
	
	void Cannon::draw()
	{
		glPushMatrix();
		{
			glTranslated(_position[0], _position[1], _position[2]); //translate the whoel cannon (cannon+wheels)
			glRotated(-90, 0, 1, 0);
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
			_position[2] = _position[2] + 0.001*elapsed_millis;
			_wheelRotation = _wheelRotation - 0.04*elapsed_millis;
		}
		if(cg::KeyBuffer::instance()->isKeyDown('s')) {
			_position[2] = _position[2] - 0.001*elapsed_millis;
			_wheelRotation = _wheelRotation + 0.04*elapsed_millis;
		}
		if(cg::KeyBuffer::instance()->isKeyDown('a') && _cannonRotation < 33) {
			_cannonRotation = _cannonRotation + 0.01*elapsed_millis;
		}
		if(cg::KeyBuffer::instance()->isKeyDown('d') && _cannonRotation > -17) {
			_cannonRotation = _cannonRotation - 0.01*elapsed_millis;
		}
	}
	
	void Cannon::placeCannon(cg::Vector3d position)
	{
		_position = position;
	}
}