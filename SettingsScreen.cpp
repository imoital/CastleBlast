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
		_settingsScreen_selectMapDay = Loader::loadTexture("Images/SettingsScreen_MapDay.png");
		_settingsScreen_night = Loader::loadTexture("Images/SettingsScreen_Night.png");
		_settingsScreen_backNight = Loader::loadTexture("Images/SettingsScreen_BackNight.png");
		_settingsScreen_startNight = Loader::loadTexture("Images/SettingsScreen_StartNight.png");
		_settingsScreen_selectMapNight = Loader::loadTexture("Images/SettingsScreen_MapNight.png");
		_settingsScreen_select1 = Loader::loadTexture("Images/SettingsScreen_SelectMap1.png");
		_settingsScreen_select1Back = Loader::loadTexture("Images/SettingsScreen_SelectMap1Back.png");
		_settingsScreen_select2 = Loader::loadTexture("Images/SettingsScreen_SelectMap2.png");
		_settingsScreen_select2Back = Loader::loadTexture("Images/SettingsScreen_SelectMap2Back.png");
		_settingsScreen_select3 = Loader::loadTexture("Images/SettingsScreen_SelectMap3.png");
		_settingsScreen_select3Back = Loader::loadTexture("Images/SettingsScreen_SelectMap3Back.png");
		
#else
		_settingsScreen_day = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_Day.png");
		_settingsScreen_backDay = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_BackDay.png");
		_settingsScreen_startDay = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_StartDay.png");
		_settingsScreen_selectMapDay = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_MapDay.png");
		_settingsScreen_night = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_Night.png");
		_settingsScreen_backNight = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_BackNight.png");
		_settingsScreen_startNight = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_StartNight.png");
		_settingsScreen_selectMapNight = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_MapNight.png");
		_settingsScreen_select1 = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_SelectMap1.png");
		_settingsScreen_select1Back = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_SelectMap1Back.png");
		_settingsScreen_select2 = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_SelectMap2.png");
		_settingsScreen_select2Back = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_SelectMap2Back.png");
		_settingsScreen_select3 = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_SelectMap3.png");
		_settingsScreen_select3Back = Loader::loadTexture("..\\..\\src\\Images\\SettingsScreen_SelectMap3Back.png");
#endif
		
		_fontsManager = (FontsManager*)cg::Registry::instance()->get("FONTS_MANAGER");
		_mapNum = 1;
		_start = false;
		_back = false;
		_day = true;
		_ambient = false;
		_selectMap = true;
		_upPressed = false;
		_downPressed = false;
		_leftPressed = false;
		_rightPressed = false;
		_mapBack = false;
		_enterSelectMap = false;
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
		
		if(_enterSelectMap) {
			if (_mapBack) {
				switch (_mapNum) {
					case 1:
						glBindTexture(GL_TEXTURE_2D, _settingsScreen_select1Back);
						break;
					case 2:
						glBindTexture(GL_TEXTURE_2D, _settingsScreen_select2Back);
						break;
					case 3:
						glBindTexture(GL_TEXTURE_2D, _settingsScreen_select3Back);
						break;
					default:
						break;
				}
			} else {
				switch (_mapNum) {
					case 1:
						glBindTexture(GL_TEXTURE_2D, _settingsScreen_select1);
						break;
					case 2:
						glBindTexture(GL_TEXTURE_2D, _settingsScreen_select2);
						break;
					case 3: 
						glBindTexture(GL_TEXTURE_2D, _settingsScreen_select3);
						break;
					default:
						break;
				}
			}
		}
		else {
			if (_day) {
				if (_selectMap)
					glBindTexture(GL_TEXTURE_2D, _settingsScreen_selectMapDay);
				else if (_back)
					glBindTexture(GL_TEXTURE_2D, _settingsScreen_backDay);
				else if (_start)
					glBindTexture(GL_TEXTURE_2D, _settingsScreen_startDay);
				else if (_ambient)
					glBindTexture(GL_TEXTURE_2D, _settingsScreen_day);
			} else {
				if (_selectMap)
					glBindTexture(GL_TEXTURE_2D, _settingsScreen_selectMapNight);
				else if (_back)
					glBindTexture(GL_TEXTURE_2D, _settingsScreen_backNight);
				else if (_start)
					glBindTexture(GL_TEXTURE_2D, _settingsScreen_startNight);
				else if (_ambient)
					glBindTexture(GL_TEXTURE_2D, _settingsScreen_night);
			}
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
	}
	
	void SettingsScreen::update(unsigned long elapsed_millis) 
	{
		if (cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_DOWN) && !_downPressed) {
			if(_enterSelectMap)
				_mapBack = true;
			else if(_selectMap){
				_selectMap = false;
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
			if(_enterSelectMap)
				_mapBack = false;
			else if(_ambient){
				_selectMap = true;
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
			if (_enterSelectMap && !_mapBack && _mapNum < 3)
				_mapNum++;
			else if (_ambient && _day)
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
			if (_enterSelectMap && !_mapBack && _mapNum > 1)
				_mapNum--;
			else if (_ambient && !_day)
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
	
	void SettingsScreen::onReshape(int width, int height)
	{
		_width = width;
		_height = height;
	}
	
	int SettingsScreen::getNumMap()
	{
		return _mapNum;
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
	
	bool SettingsScreen::isSelectMap()
	{
		return _selectMap;
	}
	
	bool SettingsScreen::isMapBack()
	{
		return _mapBack;
	}
	
	void SettingsScreen::gotoSettings()
	{
		_mapBack = false;
		_enterSelectMap = false;
		_selectMap = true;
	}
	
	void SettingsScreen::gotoSelectMap()
	{
		_selectMap = false;
		_enterSelectMap = true;
	}
}