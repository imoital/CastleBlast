//
//  Camera.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "CanonCamera.h"
namespace CastleBlast {
	
	CanonCamera::CanonCamera(Cannon *cannon) : Entity("CANON_CAMERA") 
	{
		_cannon = cannon;
	}
	CanonCamera::~CanonCamera() {
	}


	void CanonCamera::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_winWidth = win.width;
		_winHeight = win.height;
		_anglex = 0;
		_angley = 0;
		_eye.set(0,10,0);
		_center.set(10,10,0);
		_eyeInc.set(0,0,0);
		_centerInc.set(0,5,0);
		_up.set(0,1,0);
		_front.set(1,0,0);
		_right.set(0,0,1);
		_isRoll = false;
		_scale = 5.0f;
		_cannonMouseSpeed = cg::Properties::instance()->getDouble("CANNON_MOUSE_SPEED");
		
	}
	void CanonCamera::draw() {
		_cannonPos = _cannon->getPosition(); 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(65, _winWidth/(double)_winHeight, 1, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(_eye[0], _eye[1], _eye[2],
			_center[0], _center[1], _center[2],
			_up[0], _up[1], _up[2]);
	//	std::cout << _eye[0]+_eyeInc[0]<< " " << _eye[1]+_eyeInc[1]<< " " << _eye[2]+_eyeInc[2] << std::endl;
	//	std::cout << _cannonPos[0] << " " << _cannonPos[1] << " " << _cannonPos[2] << std::endl;
	}

	void CanonCamera::update(unsigned long elapsed_millis)
	{

	}

#if !defined(GLUT_WHEEL_UP)
# define GLUT_WHEEL_UP 3
# define GLUT_WHEEL_DOWN 4
#endif

	void CanonCamera::onMouse(int button, int state, int x, int y)
	{
		_lastMousePosition.set(x,y);
	}

	void CanonCamera::onMouseMotion(int x, int y)
	{	
		_anglex += _cannonMouseSpeed*(_lastMousePosition[0] - x)*PI/180;
		_angley += _cannonMouseSpeed*(_lastMousePosition[1] - y)*PI/180;
		std::cout << sin(_angley) << std::endl;
		_center[0] = 10*cos(_anglex);
		_center[2] = 10*sin(_anglex);
		_center[1] = -30*sin(_angley);
		_lastMousePosition.set(x,y);
	}

	void CanonCamera::onMousePassiveMotion(int x, int y)
	{

	}
	void CanonCamera::onReshape(int width, int height) 
	{
		_winWidth = width;
		_winHeight = height;
	}
}