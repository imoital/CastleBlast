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
		_orientation.setRotationDeg(0,cg::Vector3d::ny);
		_eye = cg::Vector3d(10,15,29);
		_center = cg::Vector3d(0,0,0);
		_up.set(0,1,0);
		_front.set(1,1,1);
		_right.set(0,0,1);
		_isRoll = false;
		_scale = 5.0f;
	}
	void WorldCamera::draw() {
		_eye = _front * _scale;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(65, _winWidth/(double)_winHeight, 1, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(_eye[0], _eye[1], _eye[2],
			_center[0], _center[1], _center[2],
			_up[0], _up[1], _up[2]);
	}

	void WorldCamera::update(unsigned long elapsed_millis)
	{
		double v = 0.001;
		cg::Vector3d vec;
		vec[0] = (_center[0] - _eye[0]);
		vec[1] = (_eye[1] + _center[1]);
		if (cg::KeyBuffer::instance()->isKeyDown('a')) {
			_eye[1] += v*vec[1]*elapsed_millis;
		}

		if (cg::KeyBuffer::instance()->isKeyDown('d')) {
			_eye[1] -= v*vec[1]*elapsed_millis;
		}

	}

#if !defined(GLUT_WHEEL_UP)
# define GLUT_WHEEL_UP 3
# define GLUT_WHEEL_DOWN 4
#endif

	void WorldCamera::onMouse(int button, int state, int x, int y)
	{
		_isRoll = (button == GLUT_RIGHT_BUTTON);
		_lastMousePosition.set(x,y);
		if (state == GLUT_UP) {
			if (button == GLUT_WHEEL_UP) 
				_scale -= 0.5f;
			else if (button == GLUT_WHEEL_DOWN)
				_scale += 0.5f;
		}
	}

	void WorldCamera::onMouseMotion(int x, int y)
	{
			double anglex = (_lastMousePosition[0] - x) / (double)5;
				_q.setRotationDeg(anglex,_up);
				_front = apply(_q,_front);
				_right = apply(_q,_right);
				_orientation = _q * _orientation;
			double angley = (y - _lastMousePosition[1]) / (double)5;
				_q.setRotationDeg(angley, _right);
				_front = apply(_q,_front);
				_orientation = _q * _orientation;
		_lastMousePosition.set(x,y);
	}

	void WorldCamera::onMousePassiveMotion(int x, int y)
	{
	}
	void WorldCamera::onReshape(int width, int height) 
	{
		_winWidth = width;
		_winHeight = height;
	}
}