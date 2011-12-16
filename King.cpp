//
//  King.cpp
//  Project
//
//  Created by Inês on 11/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "King.h"
#include "ModelManager.h"

namespace CastleBlast {
	
	King::King() : cg::Entity("KING"), Collidable(6,20,4) 
	{
		_type = "KING";
		_rotation = 0;
	}
	
	King::~King() {}
	
	void King::init()
	{
		_isAlive = true;
		_debug = false;
		_position = cg::Vector3d(0,0,0);
		
		_model = (ModelManager*)cg::Registry::instance()->get("MODEL_MANAGER");
#ifdef __APPLE__
		_model->newModel(_type, "Models/King.obj");
#else
		_model->newModel(_type, "..\\..\\src\\Models\\King.obj");
#endif
	}
	
	void King::draw()
	{
		glPushMatrix();
		{
			if (_debug)
				drawBoundingBox();
			glTranslatef(_position[0], _position[1], _position[2]);
			glRotated(_rotation, 0, 1, 0);
			glScaled(2, 2, 2);
			glEnable(GL_NORMALIZE);
			_model->drawModel(_type);
			glDisable(GL_NORMALIZE);
		}
		glPopMatrix();
	}
	
	void King::update(unsigned long elapsed_millis) 
	{
		if(cg::KeyBuffer::instance()->isKeyDown('k')) {
			_isAlive = false;
		}
	}
	
	void King::placeKing(cg::Vector3d position, float rot)
	{
		cg::Vector3d center = position;
		center[1] = center[1]+3.2;
		newPosition(center);
		_position = position;
		_rotation = (rot*180)/3.14;
		
	}
	
	void King::debugToggle()
	{
		_debug = !_debug;
	}
	
	bool King::isCollision(Collidable* obj)
	{
		boundaries otherObjBoundaries = obj->getBoundaries();
		
		if (otherObjBoundaries.x_min >= _boundes.x_min && otherObjBoundaries.x_max <= _boundes.x_max &&
		    otherObjBoundaries.y_min >= _boundes.y_min && otherObjBoundaries.y_max <= _boundes.y_max &&
		    otherObjBoundaries.z_min >= _boundes.z_min && otherObjBoundaries.z_max <= _boundes.z_max){
			_isAlive = false;
			return true;
		}
		return false;
	}
	
	bool King::isAlive()
	{
		return _isAlive;
	}
}