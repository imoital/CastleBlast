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
#include "DebugMode.h"

namespace CastleBlast {
	
	class ModelManager;
	
	class Bird : 
	public cg::Entity, 
	public cg::IDrawListener, 
	public cg::IUpdateListener, 
	public cg::IMouseEventListener,
	public Collidable,
	public DebugMode
	{
	private:
		ModelManager* _model;
		std::string _bodyName;
		std::string _wingsName;
		cg::Vector3d _position;
		float _wingRot;
		float _bodyRot;
		double _lastAngle;
		bool _toBeDeleted;
		bool _wingsUp;
		bool _wingsDown;
		bool _debug;
		
	public:
		Bird(std::string birdName);
		~Bird();
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		bool isCollision(Collidable* obj);
		bool isToDelete();
		void debugToggle();
	};
}


#endif