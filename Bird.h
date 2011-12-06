//
//  Bird.h
//  CastleBlast
//
//  Created by Inês on 12/5/11.
//  Copyright 2011 AVT. All rights reserved.
//

#ifndef BIRD_H
#define BIRD_H

#include <cg/cg.h>
#include "Collidable.h"

namespace CastleBlast {
	
	class Bird : 
	public cg::Entity, 
	public cg::IDrawListener, 
	public cg::IUpdateListener, 
	public cg::IMouseEventListener,
	public Collidable
	{
	private:
		cg::Vector3d _position;
		double _lastAngle;
		bool _toBeDeleted;
	public:
		Bird(std::string birdName);
		~Bird();
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		bool isCollision(Collidable* obj);
		bool isToDelete();
	};
}


#endif