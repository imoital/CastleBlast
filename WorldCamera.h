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
#include <Math.h>
#include "cg/cg.h"
#include "Camera.h"
#define PI 3.14159265

namespace CastleBlast {
	
	class WorldCamera : public Camera
	{
	private:
		double _winWidth, _winHeight, _anglex, _angley;
		int _mouseWheelUp, _mouseWheelDown;
		int _cameraSpeed;
		cg::Vector3d _eye, _eyeInc;
		cg:: Vector3d _center, _centerInc;
		cg::Vector2d _lastMousePosition;
		cg::Quaterniond _orientation, _q;
		bool _isRoll;
		cg::Vector3d _up,_front,_right;
		float _scale;
		
	public:
		WorldCamera();
		~WorldCamera();
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		void onReshape(int width, int height);
		void onMouse(int button, int state, int x, int y);
		void onMouseMotion(int x, int y);
		void onMousePassiveMotion(int x, int y);
		void setPos(cg::Vector3d e, cg::Vector3d c, cg::Vector3d u);

	};
}

#endif