//
//  SettingsScreen.cpp
//  CastleBlast
//
//  Created by Inês on 12/5/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include "SettingsScreen.h"
#include "Loader.h"
#include "FontsManager.h"

namespace CastleBlast {
	
	SettingsScreen::SettingsScreen()
	{
#ifdef __APPLE__
		_settingsScreenImage = Loader::loadTexture("Images/SettingsScreen.png");
#else
		_settingsScreenImage = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen.png");
#endif
		
		_fontsManager = (FontsManager*)cg::Registry::instance()->get("FONTS_MANAGER");
		_numPlayers = 2;
	}
	
	SettingsScreen::~SettingsScreen() {}

	void SettingsScreen::draw() 
	{
		glBindTexture(GL_TEXTURE_2D, _settingsScreenImage);
		
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
		
		
		std::stringstream numPlayers;
		numPlayers << _numPlayers;
		
		_fontsManager->printFont(50, 300, 1.3, 0, 1, "How many players will be playing?");
		_fontsManager->printFont(650, 300, 1.3, 0, 1, numPlayers.str());
	}
	
	void SettingsScreen::update(unsigned long elapsed_millis) 
	{
		if (cg::KeyBuffer::instance()->isKeyDown('1'))
			_numPlayers = 1;
		if (cg::KeyBuffer::instance()->isKeyDown('2'))
			_numPlayers = 2;
		if (cg::KeyBuffer::instance()->isKeyDown('3'))
			_numPlayers = 3;
		if (cg::KeyBuffer::instance()->isKeyDown('4'))
			_numPlayers = 4;
		if (cg::KeyBuffer::instance()->isKeyDown('5'))
			_numPlayers = 5;
		if (cg::KeyBuffer::instance()->isKeyDown('6'))
			_numPlayers = 6;
		if (cg::KeyBuffer::instance()->isKeyDown('7'))
			_numPlayers = 7;
		if (cg::KeyBuffer::instance()->isKeyDown('8'))
			_numPlayers = 8;
		if (cg::KeyBuffer::instance()->isKeyDown('9'))
			_numPlayers = 9;
	}
	
	int SettingsScreen::getNumPlayers()
	{
		return _numPlayers;
	}
	
}