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
	
	StartScreen::StartScreen() : cg::Entity("START_SCREEN") {}
	
	StartScreen::~StartScreen() {}
	
	void StartScreen::init() 
	{
		_startScreenImage = Loader::loadTexture("Images/StartScreen.png");
	}
	
	void StartScreen::draw() 
	{
		glBindTexture(GL_TEXTURE_2D, _startScreenImage);
		
		glDisable(GL_DEPTH_TEST);                       // Disables Depth Testing
		
		glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
		glPushMatrix();                             // Store The Projection Matrix
		glLoadIdentity();                           // Reset The Projection Matrix
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		glOrtho(0,win.width,0,win.height,-1,1);                      // Set Up An Ortho Screen
		
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
			glVertex2d(0, win.height);
			glTexCoord2d(1, 1);
			glVertex2d(win.width, win.height);
			glTexCoord2d(1, 0);
			glVertex2d(win.width, 0);
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
	
	void StartScreen::update(unsigned long elapsed_millis) {}
	
}