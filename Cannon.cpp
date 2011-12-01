//
//  Cannon.cpp
//  Project
//
//  Created by Inês on 10/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Cannon.h"
#include "ModelManager.h"
#include "Projectile.h"

namespace CastleBlast {
	
	Cannon::Cannon() :cg::Entity("CANNON") {}
	
	Cannon::~Cannon() {}
	
	void Cannon::init()
	{
		_cannon = "CANNON";
		_wheels = "WHEELS";
		_position = cg::Vector3d(0,0,0);
		_wheelRotation = 0;
		_cannonRotation = 0;
		_orientation = cg::Vector3d(0,0,1);
		_projectile = new Projectile();
		
		_model = (ModelManager*)cg::Registry::instance()->get("MODEL_MANAGER");
#ifdef __APPLE__
		_model->newModel(_cannon, "Models/cannon.obj");
		_model->newModel(_wheels, "Models/wheels.obj");
#else
		_model->newModel(_cannon, "..\\..\\src\\Models\\cannon.obj");
		_model->newModel(_wheels, "..\\..\\src\\Models\\wheels.obj");
#endif

	}
	
	void Cannon::draw()
	{
		glPushMatrix();
		{
			glTranslated(_position[0], _position[1], _position[2]); //translate the whoel cannon (cannon+wheels)
			glRotated(-90, 0, 1, 0);
			glScalef(1.5, 1.5, 1.5);
			glPushMatrix(); 
			{
				glTranslatef(.5, 1.2, 0); // translate the wheels to be in the final position
				glRotatef(_wheelRotation, 0, 0, 1); // Rotates the Wheels
				glEnable(GL_NORMALIZE);		// needs to be where because of the scale
				_model->drawModel(_wheels);	//draw the wheels
				glDisable(GL_NORMALIZE);
			}
			glPopMatrix();
		
			glPushMatrix();
			{
				glTranslatef(1, 1, 0);
				glRotatef(_cannonRotation, 0, 0, 1); // rotates the cannon
				glEnable(GL_NORMALIZE);		// needs to be where because of the scale
				_model->drawModel(_cannon);		// draw the cannon
				glDisable(GL_NORMALIZE);
			}
			glPopMatrix();
		}
		glPopMatrix();
		
		glPushMatrix();
		{
			//glTranslated(4,2,0);
			_projectile->draw();
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
		
		_projectile->update(_position, _cannonRotation, elapsed_millis);
		
		if(cg::KeyBuffer::instance()->isKeyDown(' ')) {
			_projectile->start();
		}
	}
	
	void Cannon::placeCannon(cg::Vector3d position)
	{
		_position = position;
	}
}