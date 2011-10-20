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
	
	class Cannon : public cg::Entity, public cg::IDrawListener {
	private:
		Model *_cannon;
		Model *_wheel1;
		Model *_wheel2;
		
	public:
		Cannon();
		~Cannon();
		
		void init();
		void draw();
	};
}

#endif