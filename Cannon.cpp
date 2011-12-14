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
#include "GameManager.h"

namespace CastleBlast {
	
	Cannon::Cannon(GameManager* gm) :cg::Entity("CANNON") 
	{
		_gameManager = gm;
	}
	
	Cannon::~Cannon() {}
	
	void Cannon::init()
	{
		_rotation =0;
		_cannon = "CANNON";
		_wheels = "WHEELS";
		_position = cg::Vector3d(0,0,0);
		_wheelRotation = 0;
		_cannonRotation.set(0, 0, 0);
		_projectile = new Projectile(_gameManager);
		_fire = false;
		_anglex = 0;
		_angley = 0;
		_isCannonCamera = false;
		_cannonDirection = cg::Vector3d(0,0,0);
		_force = 0;
		_orientation.setRotationDeg(0,cg::Vector3d(0,1,0));
		_right.set(0,0,1);
		_front.set(1,0,0);
		_up.set(0,1,0);

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
			glTranslated(_position[0], _position[1], _position[2]); //translate the whole cannon (cannon+wheels)
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
				glMultMatrixd(_rotationMatrix);
				glTranslatef(1, 1, 0);
				glEnable(GL_NORMALIZE);		// needs to be where because of the scale
				_model->drawModel(_cannon);		// draw the cannon
				glDisable(GL_NORMALIZE);
			}
			glPopMatrix();
		}
		glPopMatrix();
		
		glPushMatrix();
		{
			_projectile->draw();
		}
		glPopMatrix();
	
	}
	
	void Cannon::update(unsigned long elapsed_millis)
	{
		if (_isCannonCamera) {
			if(cg::KeyBuffer::instance()->isKeyDown('s')) {
				_position[2] = _position[2] + 0.001*elapsed_millis;
				_wheelRotation = _wheelRotation - 0.04*elapsed_millis;
			}
			if(cg::KeyBuffer::instance()->isKeyDown('w')) {
				_position[2] = _position[2] - 0.001*elapsed_millis;
				_wheelRotation = _wheelRotation + 0.04*elapsed_millis;
			}
		}
		
		_projectile->update(_position, _cannonDirection, _force, elapsed_millis);
		
		if(cg::KeyBuffer::instance()->isKeyDown(' ')) {
			_force = _force + 2;
			_fire = true;
			std::cout << _force << std::endl;
			if (_force == 80)
				_projectile->start();
		}
		if(cg::KeyBuffer::instance()->isKeyUp(' ') && _fire) {
			_projectile->start();
			_fire = false;
			_force = 0;
		}

	}
	
	void Cannon::placeCannon(cg::Vector3d position, int rot)
	{
		_rotation = rot;
		_position = position;
		_q.setRotationDeg(0, _right);
		_up = apply(_q,_up);
		_front = apply(_q,_front);
		_orientation = _q*_orientation;
		_orientation.getGLMatrix(_rotationMatrix);
		_q.setRotationDeg(rot,_up);
		_right = apply(_q,_right);
		_orientation = _q*_orientation;
		_orientation.getGLMatrix(_rotationMatrix);
	}

	cg::Vector3d Cannon::getPosition()
	{
		return _position;
	}

	int Cannon::getRotation()
	{
		return _rotation;
	}

	void Cannon::onMouse(int button, int state, int x, int y)
	{
		if (_isCannonCamera)
			_lastMousePosition.set(x,y);
	}

	void Cannon::onMouseMotion(int x, int y) 
	{
		if (_isCannonCamera) {
			_anglex = (_lastMousePosition[0] - x)/ (double)5;
			_angley = (_lastMousePosition[1] - y)/ (double)5;
			std::cout << _angley << std::endl;
			
			_q.setRotationDeg(_angley, _right);
			_up = apply(_q,_up);
			_front = apply(_q,_front);
			_orientation = _q*_orientation;
			_orientation.getGLMatrix(_rotationMatrix);
			_q.setRotationDeg(_anglex,_up);
			_right = apply(_q,_right);
			_orientation = _q*_orientation;
			_orientation.getGLMatrix(_rotationMatrix);
			_lastMousePosition.set(x,y);
		}
	}
	
	void Cannon::cameraToggle()
	{
		_isCannonCamera = !_isCannonCamera;
	}
	
	void Cannon::setDirection(cg::Vector3d direction)
	{
		_cannonDirection = direction;
	}
}