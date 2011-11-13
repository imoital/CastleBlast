//
//  Cannon.h
//  Project
//
//  Created by Inês on 10/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CANNON_H
#define CANNON_H

#include "Model.h"
#include "cg/cg.h"

namespace CastleBlast {
	
	class Cannon : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener {
	private:
		Model *_cannon;
		Model *_wheels;
		cg::Vector3d _position;
		float _wheelRotation;
		float _cannonRotation;
		
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