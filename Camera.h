//
//  Camera.h
//  CastleBlast
//
//  Created by Inês on 12/16/11.
//  Copyright 2011 AVT. All rights reserved.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <cg/cg.h>

namespace CastleBlast {
	class Camera : 
		public cg::Entity, public cg::IDrawListener,
		public cg::IUpdateListener, public cg::IMouseEventListener, 
		public cg::IReshapeEventListener 
	{
	public:
		Camera(std::string name) : cg::Entity(name) {}
	};
}

#endif