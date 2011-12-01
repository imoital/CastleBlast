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
	
	Collidable::Collidable(/*int x_min, int x_max, int y_min, int y_max, int z_min, int z_max*/)
	{
		_collisionManager = (CollisionManager*)cg::Registry::instance()->get("COLLISION_MANAGER");
		/*_x_min = x_min;
		_x_max = x_max;
		_y_min = y_min;
		_y_max = y_max;
		_z_min = z_min;
		_z_max = z_max;*/
	}
	
	Collidable::~Collidable() {}
	
	void Collidable::notify()
	{
		_collisionManager->verifyCollision(this);
	}
}