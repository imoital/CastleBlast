//
//  Collidable.cpp
//  Project
//
//  Created by Inês on 11/15/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include <cg/cg.h>
#include "Collidable.h"
#include "CollisionManager.h"

namespace CastleBlast {
	
	Collidable::Collidable(double Xdimension, double Ydimension, double Zdimension)
	{
		_collisionManager = (CollisionManager*)cg::Registry::instance()->get("COLLISION_MANAGER");
		_collisionManager->addCollidableObject(this);
		_boundes.Xdimension = Xdimension;
		_boundes.Ydimension = Ydimension;
		_boundes.Zdimension = Zdimension;
	}
	
	Collidable::~Collidable() {}
	
	bool Collidable::notify(cg::Vector3d position)
	{
		newPosition(position);
		return _collisionManager->verifyCollision(this);
	}
	
	Collidable::boundaries Collidable::getBoundaries()
	{
		return _boundes;
	}
	
	void Collidable::newPosition(cg::Vector3d postion)
	{
		_objPosition = postion;
		setBounderies();
	}
	
	void Collidable::setBounderies()
	{
		_boundes.x_min = _objPosition[0]-_boundes.Xdimension/2.0;
		_boundes.x_max = _objPosition[0]+_boundes.Xdimension/2.0;
		_boundes.y_min = _objPosition[1]-_boundes.Ydimension/2.0;
		_boundes.y_max = _objPosition[1]+_boundes.Ydimension/2.0;
		_boundes.z_min = _objPosition[2]-_boundes.Zdimension/2.0;
		_boundes.z_max = _objPosition[2]+_boundes.Zdimension/2.0;
	}
	
	void Collidable::drawBoundingBox()
	{
		glDisable(GL_LIGHTING);
		glColor3d(1, 1, 0);
		glBegin(GL_QUADS);
		{
			glVertex3d(_boundes.x_min, _boundes.y_min, _boundes.z_min);
			glVertex3d(_boundes.x_max, _boundes.y_min, _boundes.z_min);
			glVertex3d(_boundes.x_max, _boundes.y_max, _boundes.z_min);
			glVertex3d(_boundes.x_min, _boundes.y_max, _boundes.z_min);
			
			glVertex3d(_boundes.x_min, _boundes.y_min, _boundes.z_max);
			glVertex3d(_boundes.x_max, _boundes.y_min, _boundes.z_max);
			glVertex3d(_boundes.x_max, _boundes.y_max, _boundes.z_max);
			glVertex3d(_boundes.x_min, _boundes.y_max, _boundes.z_max);
			
			glVertex3d(_boundes.x_min, _boundes.y_min, _boundes.z_min);
			glVertex3d(_boundes.x_min, _boundes.y_min, _boundes.z_max);
			glVertex3d(_boundes.x_min, _boundes.y_max, _boundes.z_max);
			glVertex3d(_boundes.x_min, _boundes.y_max, _boundes.z_min);
			
			glVertex3d(_boundes.x_max, _boundes.y_min, _boundes.z_max);
			glVertex3d(_boundes.x_max, _boundes.y_min, _boundes.z_min);
			glVertex3d(_boundes.x_max, _boundes.y_max, _boundes.z_min);
			glVertex3d(_boundes.x_max, _boundes.y_max, _boundes.z_max);
			
			glVertex3d(_boundes.x_min, _boundes.y_max, _boundes.z_max);
			glVertex3d(_boundes.x_max, _boundes.y_max, _boundes.z_max);
			glVertex3d(_boundes.x_max, _boundes.y_max, _boundes.z_min);
			glVertex3d(_boundes.x_min, _boundes.y_max, _boundes.z_min);
			
			glVertex3d(_boundes.x_min, _boundes.y_min, _boundes.z_min);
			glVertex3d(_boundes.x_max, _boundes.y_min, _boundes.z_min);
			glVertex3d(_boundes.x_max, _boundes.y_min, _boundes.z_max);
			glVertex3d(_boundes.x_min, _boundes.y_min, _boundes.z_max);
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
}