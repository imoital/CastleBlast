//
//  Camera.h
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CANONCAMERA_H
#define CANONCAMERA_H

#include <string>
#include <Math.h>
#include "cg/cg.h"
#include "Cannon.h"
#define PI 3.14159265

namespace CastleBlast {
	

	class CanonCamera : public cg::Entity, public cg::IDrawListener, 
		public cg::IReshapeEventListener, public cg::IUpdateListener,
		public cg::IMouseEventListener
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
		cg::Vector3d _cannonPos;
		Cannon *_cannon;
		
	public:
		CanonCamera(Cannon *cannon);
		~CanonCamera();
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		void onReshape(int width, int height);
		void onMouse(int button, int state, int x, int y);
		void onMouseMotion(int x, int y);
		void onMousePassiveMotion(int x, int y);

	};
}

#endif