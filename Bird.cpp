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
	
	Bird::Bird(std::string birdName) : cg::Entity(birdName), Collidable(5,5,5) 
	{
		_bodyName = "BIRD";
		_wingsName = "WING";
	}
	
	Bird::~Bird() {}
	
	void Bird::init() 
	{
		_position = cg::Vector3d(rand()%4,42+rand()%7,rand()%4);
		_position = _position;
		_toBeDeleted = false;
		_lastAngle = (rand()%360)*180/PI;
		_wingRot = rand()%20;
		_bodyRot = 0;
		int up = rand()%2;
		_debug = false;
		
		if(up == 1)
			_wingsDown = false;
		else _wingsDown = true;
		
		_model = (ModelManager*)cg::Registry::instance()->get("MODEL_MANAGER");
#ifdef __APPLE__
		_model->newModel(_bodyName, "Models/bird.obj");
		_model->newModel(_wingsName, "Models/wing.obj");
#else
		_model->newModel(_bodyName, "..\\..\\src\\Models\\bird.obj");
		_model->newModel(_wingsName, "..\\..\\src\\Models\\wing.obj");
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
			
			if(_debug)
				drawBoundingBox();
			glTranslated(_position[0], _position[1], _position[2]);
			glRotated(_bodyRot, 0, 1, 0);
			
			glEnable(GL_NORMALIZE);
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
			glDisable(GL_NORMALIZE);
		}
		glPopMatrix();
	}
	
	void Bird::update(unsigned long elapsed_millis) 
	{
		
		_novaPos[0] = 100*cos(3*_lastAngle);

		_novaPos[2] = 100*sin(4*_lastAngle);

	/*	if( _novaPos[0] < _position[0] && _novaPos[2] > _position[2]){
			_bodyRot = atan( ( _position[0] - _novaPos[0]) /(_novaPos[2] - _position[2]));
			_bodyRot = _bodyRot * 57.692;
			printf("1\n");
		} else {
			if( _novaPos[0] < _position[0] && _novaPos[2] < _position[2]){
				_bodyRot = atan( (_position[2] - _novaPos[2]) /( _position[0] - _novaPos[0]));
				_bodyRot = _bodyRot * 57.692 + 90;
				printf("2\n");
			} else {
				if( _novaPos[0] > _position[0] && _novaPos[2] < _position[2]){
					_bodyRot = -(atan( (_novaPos[0] - _position[0]) /( _novaPos[2] - _position[2])));
					_bodyRot =  _bodyRot * 57.692 + 180;
					printf("3\n");
				} else {
					if( _novaPos[0] > _position[0] && _novaPos[2] > _position[2]){
						_bodyRot = (atan( (_novaPos[2] - _position[2]) /( _novaPos[0] - _position[0])));
						_bodyRot =  _bodyRot * 57.692 + 270;
						printf("4\n");
					}
				}
			} 
		} */

		if(_novaPos[0] > _position[0] && _novaPos[2] > _position[2]){
			_bodyRot = atan((_novaPos[0] - _position[0]) / ( _novaPos[2] - _position[2]));
			_bodyRot = _bodyRot * 57.692;
		} else {
			if(_novaPos[0] > _position[0] && _novaPos[2] < _position[2]){
				_bodyRot = atan((_position[2] - _novaPos[2]) / ( _novaPos[0] - _position[0]));
				_bodyRot = _bodyRot * 57.692 + 90;
			} else {
				if(_novaPos[0] < _position[0] && _novaPos[2] < _position[2]){
					_bodyRot = atan((_position[0] - _novaPos[0]) / ( _position[2] - _novaPos[2]));
					_bodyRot = _bodyRot * 57.692 + 180;
				} else {
					if(_novaPos[0] < _position[0] && _novaPos[2] > _position[2]){
						_bodyRot = atan((_novaPos[2] - _position[2]) / ( _position[0] - _novaPos[0]));
						_bodyRot = _bodyRot * 57.692 + 270;
					}
				}
			}
		}

		_position[0] = _novaPos[0];
		_position[2] = _novaPos[2];


		//_bodyRot = -(atan(-3*cos(3*_lastAngle)/(4*sin(4*_lastAngle)))*180)/PI;
		
		_lastAngle = _lastAngle+0.001;
		//_bodyRot = _bodyRot-0.25;
		
		
		
		if (_wingRot > 30)
			_wingsDown = true;
		if (_wingRot < -20)
			_wingsDown = false;
		
		if(_wingsDown)
			_wingRot -= elapsed_millis*0.05;
		else _wingRot += elapsed_millis*0.05;
		
		notify(_position);
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
	
	void Bird::debugToggle()
	{
		_debug = !_debug;
	}
	
}