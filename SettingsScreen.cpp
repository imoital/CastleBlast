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
		_settingsScreen_day = Loader::loadTexture("Images/SettingsScreen_Day.png");
		_settingsScreen_backDay = Loader::loadTexture("Images/SettingsScreen_BackDay.png");
		_settingsScreen_startDay = Loader::loadTexture("Images/SettingsScreen_StartDay.png");
		_settingsScreen_playersDay = Loader::loadTexture("Images/SettingsScreen_playersDay.png");
		_settingsScreen_night = Loader::loadTexture("Images/SettingsScreen_Night.png");
		_settingsScreen_backNight = Loader::loadTexture("Images/SettingsScreen_BackNight.png");
		_settingsScreen_startNight = Loader::loadTexture("Images/SettingsScreen_StartNight.png");
		_settingsScreen_playersNight = Loader::loadTexture("Images/SettingsScreen_playersNight.png");
		
#else
		_settingsScreen_day = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_Day.png");
		_settingsScreen_backDay = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_BackDay.png");
		_settingsScreen_startDay = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_StartDay.png");
		_settingsScreen_playersDay = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_playersDay.png");
		_settingsScreen_night = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_Night.png");
		_settingsScreen_backNight = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_BackNight.png");
		_settingsScreen_startNight = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_StartNight.png");
		_settingsScreen_playersNight = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_playersNight.png");
#endif
		
		_fontsManager = (FontsManager*)cg::Registry::instance()->get("FONTS_MANAGER");
		_numPlayers = 2;
		_start = false;
		_back = false;
		_day = true;
		_ambient = false;
		_players = true;
		_upPressed = false;
		_downPressed = false;
		_leftPressed = false;
		_rightPressed = false;
	}
	
	SettingsScreen::~SettingsScreen() {}
	
	void SettingsScreen::init()
	{
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_width = win.width;
		_height = win.height;
	}

	void SettingsScreen::draw() 
	{
		
		if (_day) {
			if (_players)
				glBindTexture(GL_TEXTURE_2D, _settingsScreen_playersDay);
			else if (_back)
				glBindTexture(GL_TEXTURE_2D, _settingsScreen_backDay);
			else if (_start)
				glBindTexture(GL_TEXTURE_2D, _settingsScreen_startDay);
			else if (_ambient)
				glBindTexture(GL_TEXTURE_2D, _settingsScreen_day);
		} else {
			if (_players)
				glBindTexture(GL_TEXTURE_2D, _settingsScreen_playersNight);
			else if (_back)
				glBindTexture(GL_TEXTURE_2D, _settingsScreen_backNight);
			else if (_start)
				glBindTexture(GL_TEXTURE_2D, _settingsScreen_startNight);
			else if (_ambient)
				glBindTexture(GL_TEXTURE_2D, _settingsScreen_night);
		}
		
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
		
		
		std::stringstream numPlayers;
		numPlayers << _numPlayers;
		
		_fontsManager->printFont(_width/2.0, _height/2.0 + _height/12.0, 2.7, 0, 1, numPlayers.str());
	}
	
	void SettingsScreen::update(unsigned long elapsed_millis) 
	{
		if (_players) {
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
		if (cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_DOWN) && !_downPressed) {
			if(_players){
				_players = false;
				_ambient = true;
			} else if (_ambient) {
				_ambient = false;
				_back = true;
			}
			_downPressed = true;
		}
		if (cg::KeyBuffer::instance()->isSpecialKeyUp(GLUT_KEY_DOWN) && _downPressed)
			_downPressed = false;
		
		if (cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_UP) && !_upPressed) {
			if(_ambient){
				_players = true;
				_ambient = false;
			} else if (_back || _start) {
				_ambient = true;
				_back = false;
				_start = false;
			}
			_upPressed = true;
		}
		if (cg::KeyBuffer::instance()->isSpecialKeyUp(GLUT_KEY_UP) && _upPressed)
			_upPressed = false;
		
		if (cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_RIGHT) && !_rightPressed) {
			if (_ambient && _day)
				_day = false;
			else if (_back) {
				_back = false;
				_start = true;
			}
			_rightPressed = true;
		}
		
		if (cg::KeyBuffer::instance()->isSpecialKeyUp(GLUT_KEY_RIGHT) && _rightPressed)
			_rightPressed = false;
		
		if (cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_LEFT) && !_leftPressed) {
			if (_ambient && !_day)
				_day = true;
			else if (_start) {
				_back = true;
				_start = false;
			}
			_leftPressed = true;
		}
		
		if (cg::KeyBuffer::instance()->isSpecialKeyUp(GLUT_KEY_LEFT) && _leftPressed)
			_leftPressed = false;
	}
	
	int SettingsScreen::getNumPlayers()
	{
		return _numPlayers;
	}
	
	void SettingsScreen::onReshape(int width, int height)
	{
		_width = width;
		_height = height;
	}
	
	bool SettingsScreen::isDay()
	{
		return _day;
	}
	
	bool SettingsScreen::isStart()
	{
		return _start;
	}
	
	bool SettingsScreen::isBack()
	{
		return _back;
	}
	
}