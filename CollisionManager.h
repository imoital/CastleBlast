//
//  CollisionManager.h
//  Project
//
//  Created by Inês on 11/15/11.
//  Copyright 2011 AVT. All rights reserved.
//

#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <cg/cg.h>

namespace CastleBlast {
	
	class Collidable;
	
	class CollisionManager : cg::Entity {
		
	private:
		std::vector<Collidable*> _collidableObjects;
		
	public:
		CollisionManager();
		~CollisionManager();
		
		void init();
		void addCollidableObject(Collidable* obj);
		
		bool verifyCollision(Collidable *obj);
	};
}

#endif