//
//  Camera.cpp
//  Project
//
//  Created by In�s on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "CannonCamera.h"
#include "Loader.h"
#include "Wind.h"
#include "GameManager.h"

namespace CastleBlast {
	
	CannonCamera::CannonCamera(Cannon *cannon) : Camera("CANNON_CAMERA") 
	{
		_cannon = cannon;
	}
	CannonCamera::~CannonCamera() {
	}

	void CannonCamera::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_winWidth = win.width;
		_winHeight = win.height;
		_orientation.setRotationDeg(0,cg::Vector3d::ny);
		_eye.set(0,0,0);
		_center.set(0,0,0);
		_eyeInc.set(0,5,0);
		//_centerInc.set(0,5,0);
		_up.set(0,1,0);
		_front.set(1,0,0);
		_right.set(0,0,1);
		_isRoll = false;
		_scale = 150.0f;
		MAX_FORCE = cg::Properties::instance()->getInt("MAX_FORCE");
		MAX_WIND = cg::Properties::instance()->getInt("MAX_WIND");
		/* Initialize camera position */
		_cameraSpeed = cg::Properties::instance()->getInt("CAMERA_SPEED");
		GameManager* gm = (GameManager*)cg::Registry::instance()->get("GAME_MANAGER");
		_wind = (Wind*) gm->get("WIND");
		
#ifdef __APPLE__
		_forceTexture = Loader::loadTexture("Textures/forceBar.png");
		_windTexture = Loader::loadTexture("Textures/windBar.png");
#else
		_forceTexture = Loader::loadTexture("..\\..\\src\\Textures\\forceBar.png");
		_windTexture = Loader::loadTexture("..\\..\\src\\Textures\\windBar.png");
#endif
		
	}
	void CannonCamera::draw() 
	{
		_center = -_front * _scale;
		_cannonPos = _cannon->getPosition();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(65, _winWidth/(double)_winHeight, 1, 500);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(_eye[0]+_cannonPos[0], _eye[1]+_cannonPos[1]+6, _eye[2]+_cannonPos[2],
			_center[0]+_cannonPos[0], _center[1]+_cannonPos[1]+6, _center[2]+_cannonPos[2],
			_up[0], _up[1], _up[2]);
	}

	cg::Vector3d CannonCamera::getEpos(){
		return _eye;
	}

	cg::Vector3d CannonCamera::getCpos(){
		return _center;
	}

	cg::Vector3d CannonCamera::getUpos(){
		return _up;
	}

	void CannonCamera::update(unsigned long elapsed_millis)
	{
		if (cg::KeyBuffer::instance()->isKeyDown('a')) {
			_eyeInc[0] -= _cameraSpeed*_front[2];
			_eyeInc[2] += _cameraSpeed*_front[0];
			_centerInc[0] -= _cameraSpeed*_front[2];
			_centerInc[2] += _cameraSpeed*_front[0];
		}
		if (cg::KeyBuffer::instance()->isKeyDown('d')) {
			_eyeInc[0] += _cameraSpeed*_front[2];
			_eyeInc[2] -= _cameraSpeed*_front[0];
			_centerInc[0] += _cameraSpeed*_front[2];
			_centerInc[2] -= _cameraSpeed*_front[0];
		}
		if (cg::KeyBuffer::instance()->isKeyDown('w')) {
			_eyeInc[0] -= _cameraSpeed*_front[0];
			_eyeInc[2] -= _cameraSpeed*_front[2];
			_centerInc[0] -= _cameraSpeed*_front[0];
			_centerInc[2] -= _cameraSpeed*_front[2];
		}
		if (cg::KeyBuffer::instance()->isKeyDown('s')) {
			_eyeInc[0] += _cameraSpeed*_front[0];
			_eyeInc[2] += _cameraSpeed*_front[2];
			_centerInc[0] += _cameraSpeed*_front[0];
			_centerInc[2] += _cameraSpeed*_front[2];
		}
		
		cg::Vector3d directionEye;
		directionEye[0] = _eye[0]+_cannonPos[0];
		directionEye[1] = _eye[1]+_cannonPos[1]+5;
		directionEye[2] = _eye[2]+_cannonPos[2];
		
		cg::Vector3d directionCenter;
		directionCenter[0] = _center[0]+_cannonPos[0];
		directionCenter[1] = _center[1]+_cannonPos[1]+5;
		directionCenter[2] = _center[2]+_cannonPos[2];
		
		_cannon->setDirection(normalize(directionCenter-directionEye));
	}

#if !defined(GLUT_WHEEL_UP)
# define GLUT_WHEEL_UP 3
# define GLUT_WHEEL_DOWN 4
#endif

	void CannonCamera::onMouse(int button, int state, int x, int y)
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

	void CannonCamera::onMouseMotion(int x, int y)
	{	
		double anglex = (_lastMousePosition[0] - x) / (double)5;
			_q.setRotationDeg(anglex,_up);
			_front = apply(_q,_front);
			_right = apply(_q,_right);
		double angley = (y - _lastMousePosition[1]) / (double)5;
			_q.setRotationDeg(angley, _right);
			_front = apply(_q,_front);
		_lastMousePosition.set(x,y);
	}

	void CannonCamera::onMousePassiveMotion(int x, int y)
	{

	}
	void CannonCamera::onReshape(int width, int height) 
	{
		_winWidth = width;
		_winHeight = height;
	}

	void CannonCamera::setInitialRotation(int rot)
	{
		_q.setRotationRad(rot + PI/2,_up);
		_front = apply(_q,_front);
		_right = apply(_q,_right);
		_q.setRotationDeg(15, _right);
		_front = apply(_q,_front);
	}
	
	void CannonCamera::drawOverlay()
	{
		double cannonForce = _cannon->getForce();
		
		if(!_cannon->hasStart()) {
			
			
			glDisable(GL_DEPTH_TEST);                       // Disables Depth Testing
			
			glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
			glPushMatrix();                             // Store The Projection Matrix
			glLoadIdentity();                           // Reset The Projection Matrix
			glOrtho(0,_winWidth,0,_winHeight,-1,1);                      // Set Up An Ortho Screen
			
			glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
			glPushMatrix();                             // Store The Modelview Matrix
			glLoadIdentity();                           // Reset The Modelview Matrix
			
			glDisable(GL_LIGHTING);
			glColor3d(1, 1, 1);
			glBindTexture(GL_TEXTURE_2D, _forceTexture);
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			{
				glTexCoord2d(0, 0);
				glVertex2d(_winWidth-60, 10);
				glTexCoord2d(1, 0);
				glVertex2d(_winWidth-40, 10);
				glTexCoord2d(1, cannonForce/MAX_FORCE);
				glVertex2d(_winWidth-40, 10 + (cannonForce*70)/MAX_FORCE);
				glTexCoord2d(0, cannonForce/MAX_FORCE);
				glVertex2d(_winWidth-60, 10 + (cannonForce*70)/MAX_FORCE);
			}
			glEnd(); 
			
			glBindTexture(GL_TEXTURE_2D, _windTexture);
			cg::Vector3d windForce = _wind->getWind();
			int cameraDirection = _eye[2] - _center[2];
			if (cameraDirection >= 0) {
				if (windForce[0] >= 0) {
					glBegin(GL_QUADS);
					{
						glTexCoord2d(0, 0);
						glVertex2d(_winWidth/2.0 + 5, _winHeight - _winHeight/15.0);
						glTexCoord2d(windForce[0]/MAX_WIND, 0);
						glVertex2d(_winWidth/2.0 + 5 + (abs(windForce[0])*300)/MAX_WIND, _winHeight - _winHeight/15.0);
						glTexCoord2d(windForce[0]/MAX_WIND, 1);
						glVertex2d(_winWidth/2.0 + 5 + (abs(windForce[0])*300)/MAX_WIND, _winHeight - _winHeight/30.0);
						glTexCoord2d(0, 1);
						glVertex2d(_winWidth/2.0 + 5, _winHeight - _winHeight/30.0);
					}
					glEnd();
				} else {
					glBegin(GL_QUADS);
					{
						glTexCoord2d(0, 0);
						glVertex2d(_winWidth/2.0 - 5, _winHeight - _winHeight/15.0);
						glTexCoord2d(windForce[0]/MAX_WIND, 0);
						glVertex2d(_winWidth/2.0 - 5 - (abs(windForce[0])*300)/MAX_WIND, _winHeight - _winHeight/15.0);
						glTexCoord2d(windForce[0]/MAX_WIND, 1);
						glVertex2d(_winWidth/2.0 - 5 - (abs(windForce[0])*300)/MAX_WIND, _winHeight - _winHeight/30.0);
						glTexCoord2d(0, 1);
						glVertex2d(_winWidth/2.0 - 5, _winHeight - _winHeight/30.0);
					}
					glEnd();
				}
			} else {
				if (windForce[0] <= 0) {
					glBegin(GL_QUADS);
					{
						glTexCoord2d(0, 0);
						glVertex2d(_winWidth/2.0 + 5, _winHeight - _winHeight/15.0);
						glTexCoord2d(windForce[0]/MAX_WIND, 0);
						glVertex2d(_winWidth/2.0 + 5 + (abs(windForce[0])*300)/MAX_WIND, _winHeight - _winHeight/15.0);
						glTexCoord2d(windForce[0]/MAX_WIND, 1);
						glVertex2d(_winWidth/2.0 + 5 + (abs(windForce[0])*300)/MAX_WIND, _winHeight - _winHeight/30.0);
						glTexCoord2d(0, 1);
						glVertex2d(_winWidth/2.0 + 5, _winHeight - _winHeight/30.0);
					}
					glEnd();
				} else {
					glBegin(GL_QUADS);
					{
						glTexCoord2d(0, 0);
						glVertex2d(_winWidth/2.0 - 5, _winHeight - _winHeight/15.0);
						glTexCoord2d(windForce[0]/MAX_WIND, 0);
						glVertex2d(_winWidth/2.0 - 5 - (abs(windForce[0])*300)/MAX_WIND, _winHeight - _winHeight/15.0);
						glTexCoord2d(windForce[0]/MAX_WIND, 1);
						glVertex2d(_winWidth/2.0 - 5 - (abs(windForce[0])*300)/MAX_WIND, _winHeight - _winHeight/30.0);
						glTexCoord2d(0, 1);
						glVertex2d(_winWidth/2.0 - 5, _winHeight - _winHeight/30.0);
					}
					glEnd();
				}
			}
			
			
			glColor3d(_lineColor[0], _lineColor[1], _lineColor[2]);
			glLineWidth(2);
			glBegin(GL_LINE_STRIP);
			{
				glVertex2d(_winWidth/2.0, _winHeight - _winHeight/30.0);
				glVertex2d(_winWidth/2.0, _winHeight - _winHeight/15.0);
			}
			glEnd();
			glLineWidth(1.f); //reset
			
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_LIGHTING);
			glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
			glPopMatrix();                              // Restore The Old Projection Matrix
			
			glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
			glPopMatrix();                              // Restore The Old Projection Matrix
			
			glEnable(GL_DEPTH_TEST);
		}
		
	}
	
	void CannonCamera::setLineColor(double r, double g, double b)
	{
		_lineColor = cg::Vector3d(r, g, b);
	}
}