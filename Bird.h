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

namespace CastleBlast {
	
	class Bird : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener, public cg::IMouseEventListener
	{
	private:
		cg::Vector3d _position;
		double _lastAngle;
	public:
		Bird(std::string birdName);
		~Bird();
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
	};
}


#endif