//
//  Camera.h
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef WORLDCAMERA_H
#define WORLDCAMERA_H

#include <string>
#include "cg/cg.h"

namespace CastleBlast {
	
	class WorldCamera : public cg::Entity, public cg::IDrawListener, public cg::IReshapeEventListener
	{
	private:
		double _winWidth, _winHeight;
		
	public:
		WorldCamera();
		~WorldCamera();
		void init();
		void draw();
		void onReshape(int width, int height);
	};
}

#endif