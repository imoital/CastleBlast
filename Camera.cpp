//
//  Camera.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Camera.h"

namespace AVT {
	
	Camera::Camera(const std::string& id) : Entity(id) {
	}
	Camera::~Camera() {
	}
	void Camera::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_winWidth = win.width;
		_winHeight = win.height;
	}
	void Camera::draw() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,_winWidth,0,_winHeight,0,-100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	void Camera::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
}