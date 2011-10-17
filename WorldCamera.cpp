//
//  Camera.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "WorldCamera.h"

namespace CastleBlast {
	
	WorldCamera::WorldCamera() : Entity("WORLD_CAMERA") {
	}
	WorldCamera::~WorldCamera() {
	}
	void WorldCamera::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_winWidth = win.width;
		_winHeight = win.height;
	}
	void WorldCamera::draw() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(0,_winWidth,0,_winHeight,0,-100);
		gluPerspective(65, _winWidth/(double)_winHeight, 1, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(10, 15, 29, 0, 0, 0, 0, 1, 0);
	}
	void WorldCamera::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
}