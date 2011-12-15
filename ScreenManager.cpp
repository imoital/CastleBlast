//
//  ScreenManager.cpp
//  CastleBlast
//
//  Created by Inês on 12/5/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include "ScreenManager.h"
#include "StartScreen.h"
#include "SettingsScreen.h"
#include "GameManager.h"

#define GLUT_KEY_RETURN 13

namespace CastleBlast {
	
	ScreenManager::ScreenManager() : cg::Entity("SCREEN_MANAGER") {}
	
	ScreenManager::~ScreenManager() {}
	
	void ScreenManager::init()
	{
		_startScreen = new StartScreen();
		_settingScreen = new SettingsScreen();
		_isStartScreen = true;
		_isReturnPressed = false;
	}
	
	void ScreenManager::draw()
	{
		if (_isStartScreen)
			_startScreen->draw();
		else _settingScreen->draw();
	} 
	
	void ScreenManager::update(unsigned long elapsed_millis)
	{
		if (_isStartScreen)
			_startScreen->update(elapsed_millis);
		else _settingScreen->update(elapsed_millis);
		
		GameManager *gameManager = (GameManager*)cg::Registry::instance()->get("GAME_MANAGER");
		
		if (cg::KeyBuffer::instance()->isKeyDown(GLUT_KEY_RETURN) && !_isReturnPressed) {
			if (_isStartScreen) {
				if(_startScreen->isStart())
					gameManager->startGame(2, 1);
				if(!_startScreen->isStart()) {
					_isStartScreen = false;
					_isReturnPressed =true;
				}
			} else {
				if(_settingScreen->isStart()) {
					if (_settingScreen->isDay())
						gameManager->startGame(_settingScreen->getNumPlayers(), DAY);
					else
						gameManager->startGame(_settingScreen->getNumPlayers(), NIGHT);
				} else if (_settingScreen->isBack()) {
					_isStartScreen = true;
				}
			}
			_isReturnPressed = true;
		}
		
		if(cg::KeyBuffer::instance()->isKeyUp(GLUT_KEY_RETURN) && _isReturnPressed)
			_isReturnPressed = false;
	}
	
	void ScreenManager::onMouse(int button, int state, int x, int y)
	{
	}
	
	void ScreenManager::onReshape(int width, int height)
	{
		_startScreen->onReshape(width, height);
		_settingScreen->onReshape(width, height);
	}
}