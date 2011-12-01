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
	
	class Cannon : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener {
	private:
		std::string _cannon;
		std::string _wheels;
		ModelManager* _model;
		cg::Vector3d _position;
		float _wheelRotation;
		float _cannonRotation;
		cg::Vector3d _orientation;
		Projectile* _projectile;
		
	public:
		Cannon();
		~Cannon();
		
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		void placeCannon(cg::Vector3d position);
	};
}

#endif