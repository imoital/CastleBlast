//
//  Bird.cpp
//  CastleBlast
//
//  Created by Inês on 12/5/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include "Bird.h"

namespace CastleBlast {
	
	Bird::Bird(std::string birdName) : cg::Entity(birdName), Collidable(2,2,2) {}
	
	Bird::~Bird() {}
	
	void Bird::init() 
	{
		_position = cg::Vector3d(rand()%4,42+rand()%7,rand()%4);
		_toBeDeleted = false;
		_lastAngle = rand()%360;
	}
	
	void Bird::draw() 
	{
		GLfloat mat_emission[] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat mat_ambient[] = {0.2f,0.2f,0.7f,1.0f};
		GLfloat mat_diffuse[] = {0.2f,0.2f,0.7f,1.0f};
		GLfloat mat_specular[] = {0.2f,0.2f,0.7f,1.0f};
		GLfloat mat_shininess[] = {1.0f};
		glPushMatrix();
		{
			glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);
			glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
			
			glTranslated(_position[0], _position[1], _position[2]);
			glutSolidSphere(1, 16, 16);
		}
		glPopMatrix();
	}
	
	void Bird::update(unsigned long elapsed_millis) 
	{
		_position[0] = 100*cos(3*_lastAngle);
		_position[2] = 100*sin(4*_lastAngle);
		_lastAngle = _lastAngle+0.001;
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