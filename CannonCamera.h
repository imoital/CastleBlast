//
//  Camera.h
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CANNONCAMERA_H
#define CANNONCAMERA_H

#include <string>
#include <Math.h>
#include "cg/cg.h"
#include "Cannon.h"
#include "Camera.h"
#define PI 3.14159265

namespace CastleBlast {
	

	class CannonCamera : public Camera
	{
	private:
		double _winWidth, _winHeight, _anglex, _angley;
		int _mouseWheelUp, _mouseWheelDown;
		int _cameraSpeed;
		cg::Vector3d _eye, _eyeInc;
		cg:: Vector3d _center, _centerInc, _cannonPos;
		cg::Vector2d _lastMousePosition;
		cg::Quaterniond _orientation, _q;
		bool _isRoll;
		cg::Vector3d _up,_front,_right;
		float _scale;
		Cannon *_cannon;
		GLuint _forceTexture;
		int MAX_FORCE;

		
	public:
		CannonCamera(Cannon* cannon);
		~CannonCamera();
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		void onReshape(int width, int height);
		void onMouse(int button, int state, int x, int y);
		void onMouseMotion(int x, int y);
		void onMousePassiveMotion(int x, int y);
		void setInitialRotation(int rot);
		cg::Vector3d getEpos();
		cg::Vector3d getCpos();
		cg::Vector3d getUpos();
		void drawOverlay();

	};
}

#endif