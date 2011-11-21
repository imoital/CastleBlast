//
//  CollisionManager.cpp
//  Project
//
//  Created by Inês on 11/15/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include "CollisionManager.h"
#include "Collidable.h"

namespace CastleBlast {
	
	CollisionManager::CollisionManager() : cg::Entity("COLLISION_MANAGER"){}
	
	CollisionManager::~CollisionManager() {}
	
	void CollisionManager::init() {}
	
	void CollisionManager::addCollidableObject(CastleBlast::Collidable *obj)
	{
		_collidableObjects.push_back(obj);
	}
	
	bool CollisionManager::verifyCollision(CastleBlast::Collidable *obj) {}
}
