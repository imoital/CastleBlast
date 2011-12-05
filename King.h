//
//  King.h
//  Project
//
//  Created by Inês on 11/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef KING_H
#define KING_H
#include "cg/cg.h"
#include "Collidable.h"
#include "DebugMode.h"

namespace CastleBlast {
	
	class ModelManager;
	
	class King : 
	public cg::Entity, 
	public cg::IDrawListener, 
	public cg::IUpdateListener, 
	public cg::IMouseEventListener, 
	public Collidable,
	public DebugMode
	{
	private:
		ModelManager* _model;
		cg::Vector3d _position;
		std::string _type;
		bool _alive;
		bool _debug;
		
	public:
		King();
		~King();
		
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		void placeKing(cg::Vector3d position);
		void debugToggle();
		bool isCollision(Collidable* obj);
	};
}
#endif