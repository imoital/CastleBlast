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
	
	bool CollisionManager::verifyCollision(CastleBlast::Collidable *obj) { 
		
		bool collided = false;
		
		for (int i = 0; i < _collidableObjects.size(); i++) {
			if (_collidableObjects[i] != obj)
				collided = collided || _collidableObjects[i]->isCollision(obj);
		}
		
		return collided;
	
	}
}
