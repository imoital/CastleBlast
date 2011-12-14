//
//  Bird.cpp
//  CastleBlast
//
//  Created by Inês on 12/5/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include "Bird.h"
#include "ModelManager.h"
#define PI 3.14

namespace CastleBlast {
	
	Bird::Bird(std::string birdName) : cg::Entity(birdName), Collidable(2,2,2) 
	{
		_bodyName = "BIRD";
		_wingsName = "WING";
	}
	
	Bird::~Bird() {}
	
	void Bird::init() 
	{
		_position = cg::Vector3d(rand()%4,42+rand()%7,rand()%4);
		_toBeDeleted = false;
		_lastAngle = (rand()%360)*180/PI;
		_wingRot = rand()%20;
		_bodyRot = (tan(_lastAngle)*PI)/180.0;
		int up = rand()%2;
		
		if(up == 1)
			_wingsDown = false;
		else _wingsDown = true;
		
		_model = (ModelManager*)cg::Registry::instance()->get("MODEL_MANAGER");
#ifdef __APPLE__
		_model->newModel(_bodyName, "Models/bird.obj");
		_model->newModel(_wingsName, "Models/wing.obj");
#else
		_model->newModel(_bodyName, "..\\..\\src\\Models\\bird.obj");
		_model->newModel(_bodyName, "..\\..\\src\\Models\\wing.obj");
#endif
	}
	
	void Bird::draw() 
	{
		GLfloat mat_emission[] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat mat_ambient[] = {0.2f,0.2f,0.7f,1.0f};
		GLfloat mat_diffuse[] = {0.2f,0.2f,0.7f,1.0f};
		GLfloat mat_specular[] = {0.2f,0.2f,0.7f,1.0f};
		GLfloat mat_shininess[] = {0.1f};
		glPushMatrix();
		{
			glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);
			glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
			
			glScaled(0.7, 0.7, 0.7);
			glTranslated(_position[0], _position[1], _position[2]);
			glRotated(_bodyRot, 0, 1, 0);
			
			_model->drawModel(_bodyName);
			
			glPushMatrix();
			{
				glRotated(_wingRot, 0, 0, 1);
				_model->drawModel(_wingsName);
			}
			glPopMatrix();
			
			glPushMatrix();
			{
				glRotated(-_wingRot, 0, 0, 1);
				glRotated(180, 0, 1, 0);
				_model->drawModel(_wingsName);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	
	void Bird::update(unsigned long elapsed_millis) 
	{
		_position[0] = 100*cos(3*_lastAngle);
		_position[2] = 100*sin(4*_lastAngle);
		
		_bodyRot = -(atan(-3*cos(3*_lastAngle)/(4*sin(4*_lastAngle)))*180)/PI;
		std::cout << "---------------bird " << _bodyRot << std::endl;
		
		_lastAngle = _lastAngle+0.001;
		//_bodyRot = _bodyRot-0.25;
		
		if(_bodyRot >= 360)
			_bodyRot = 0;
		
		if (_wingRot > 30)
			_wingsDown = true;
		if (_wingRot < -20)
			_wingsDown = false;
		
		if(_wingsDown)
			_wingRot -= elapsed_millis*0.05;
		else _wingRot += elapsed_millis*0.05;
	}
	
	bool Bird::isCollision(CastleBlast::Collidable *obj)
	{
		Collidable::boundaries otherBoundaries = obj->getBoundaries();
		
		if ((_boundes.x_min >= otherBoundaries.x_min) &&
		    (_boundes.x_max <= otherBoundaries.x_max) &&
		    (_boundes.y_min >= otherBoundaries.y_min) &&
		    (_boundes.y_max <= otherBoundaries.y_max) &&
		    (_boundes.z_min >= otherBoundaries.z_min) &&
		    (_boundes.z_max <= otherBoundaries.z_max)) {
			_toBeDeleted = true;
			return true;
		}
		else return false;
	}
	
	bool Bird::isToDelete()
	{
		return _toBeDeleted;
	}
	
}