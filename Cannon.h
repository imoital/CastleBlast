//
//  Cannon.h
//  Project
//
//  Created by Inês on 10/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef CANNON_H
#define CANNON_H

#include "cg/cg.h"

namespace CastleBlast {
	
	class ModelManager;
	class Projectile;
	class GameManager;

	class Cannon : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener, public cg::IMouseEventListener 
	{
	private:
		std::string _cannon;
		std::string _wheels;
		cg::Vector2d _lastMousePosition;
		cg::Vector3d _cannonRotation;
		cg::Vector3d _right, _up, _front;
		int _rotation;
		double _anglex, _angley;
		ModelManager* _model;
		cg::Vector3d _position;
		float _wheelRotation;
		Projectile* _projectile;
		GameManager* _gameManager;
		bool _fire;
		bool _isCannonCamera;
		cg::Vector3d _cannonDirection;

		double _rotationMatrix[16];
		cg::Quaterniond _q;
		cg::Quaterniond _orientation;
		
	public:
		Cannon(GameManager* gm);
		~Cannon();
		
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		void placeCannon(cg::Vector3d position, int rot);
		cg::Vector3d getPosition();
		void onMouseMotion(int x, int y);
		void onMouse(int button, int state, int x, int y);
		void cameraToggle();
		void setDirection(cg::Vector3d direction);
		int getRotation();
	};
}

#endif