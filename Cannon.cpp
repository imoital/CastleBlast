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
			glScaled(2, 2, 2);
			glPushMatrix();
			{
				glTranslatef(_position[0]+.5, _position[1]+1.7, _position[2]);
				glRotatef(_wheelRotation, 0, 0, 1);
				_wheels->drawModel();
			}
			glPopMatrix();
		
			glPushMatrix();
			{
				glTranslatef(_position[0], _position[1], _position[2]);
				glRotatef(_cannonRotation, 0, 0, 1);
				glEnable(GL_NORMALIZE);
				_cannon->drawModel();
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