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
	
	King::King() : cg::Entity("KING") 
	{
		_type = "KING";
	}
	
	King::~King() {}
	
	void King::init()
	{
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
			glTranslatef(_position[0], _position[1], _position[2]);
			_model->drawModel(_type);
		}
		glPopMatrix();
	}
	
	void King::update(unsigned long elapsed_millis) {}
	
	void King::placeKing(cg::Vector3d position)
	{
		_position = position;
	}
}