//
//  StartScreen.cpp
//  CastleBlast
//
//  Created by Inês on 12/4/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include "StartScreen.h"
#include "Loader.h"

namespace CastleBlast {
	
	StartScreen::StartScreen()
	{
#ifdef __APPLE__
		_startScreenImage = Loader::loadTexture("Images/StartScreen_Start.png");
		_settingsScreenImage = Loader::loadTexture("Images/StartScreen_Settings.png");
#else
		_startScreenImage = Loader::loadTexture("..\\..\\src\\Images\\StartScreen_Start.png");
		_settingsScreenImage = Loader::loadTexture("..\\..\\src\\Images\\StartScreen_Settings.png");
#endif
	}
	
	StartScreen::~StartScreen() {}
	
	void StartScreen::init()
	{
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_width = win.width;
		_height = win.height;
		_start = true;
	}
	
	void StartScreen::draw() 
	{
		if(_start)
			glBindTexture(GL_TEXTURE_2D, _startScreenImage);
		else 
			glBindTexture(GL_TEXTURE_2D, _settingsScreenImage);
		
		glDisable(GL_DEPTH_TEST);                       // Disables Depth Testing
		
		glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
		glPushMatrix();                             // Store The Projection Matrix
		glLoadIdentity();                           // Reset The Projection Matrix
		glOrtho(0,_width,0,_height,-1,1);                      // Set Up An Ortho Screen
		
		glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
		glPushMatrix();                             // Store The Modelview Matrix
		glLoadIdentity();                           // Reset The Modelview Matrix
		
		glDisable(GL_LIGHTING);
		glColor3d(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		{
			glTexCoord2d(0, 0);
			glVertex2d(0, 0);
			glTexCoord2d(0, 1);
			glVertex2d(0, _height);
			glTexCoord2d(1, 1);
			glVertex2d(_width, _height);
			glTexCoord2d(1, 0);
			glVertex2d(_width, 0);
		}
		glEnd(); 
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
		glPopMatrix();                              // Restore The Old Projection Matrix
		
		glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
		glPopMatrix();                              // Restore The Old Projection Matrix
		
		glEnable(GL_DEPTH_TEST);
	}
	
	void StartScreen::update(unsigned long elapsed_millis) 
	{
		if(cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_DOWN))
			_start = false;
		if(cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_UP))
			_start = true;
	}
	
	void StartScreen::onReshape(int width, int height)
	{
		_width = width;
		_height = height;
	}
	
	bool StartScreen::isStart()
	{
		return _start;
	}
	
	void StartScreen::restart()
	{
		_start = true;
	}
}