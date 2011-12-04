//
//  Cannon.h
//  Project
//
//  Created by Inês on 10/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CANNON_H
#define CANNON_H

#include "cg/cg.h"

namespace CastleBlast {
	
	class ModelManager;
	class Projectile;
	
	class Cannon : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener, public cg::IMouseEventListener 
	{
	private:
		std::string _cannon;
		std::string _wheels;
		cg::Vector2d _lastMousePosition;
		cg::Vector3d _cannonRotation;
		double _anglex, _angley;
		ModelManager* _model;
		cg::Vector3d _position;
		float _wheelRotation;
		cg::Vector3d _orientation;
		Projectile* _projectile;
		bool _fire;
		
	public:
		Cannon();
		~Cannon();
		
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		void placeCannon(cg::Vector3d position);
		cg::Vector3d getPosition();
		void onMouseMotion(int x, int y);
		void onMouse(int button, int state, int x, int y);
	};
}

#endif