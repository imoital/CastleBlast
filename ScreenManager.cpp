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

namespace CastleBlast {
	
	ScreenManager::ScreenManager() : cg::Entity("SCREEN_MANAGER") {}
	
	ScreenManager::~ScreenManager() {}
	
	void ScreenManager::init()
	{
		_startScreen = new StartScreen();
		_settingScreen = new SettingsScreen();
		_isStartScreen = true;
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
	}
	
	void ScreenManager::onMouse(int button, int state, int x, int y)
	{
		GameManager *gameManager = (GameManager*)cg::Registry::instance()->get("GAME_MANAGER");
		if (_isStartScreen) {
			if(x >= 265 && x <= 555 && y >= 270 && y <= 330)
				gameManager->startGame(2);
			if(x >= 265 && x <= 555 && y >= 384 && y <= 444)
				_isStartScreen = false;
		}
		else {
			std::cout << "" << x << " " << y << std::endl;
			if (x >= 72 && x <= 357 && y >= 485 && y <= 545) {
				_isStartScreen = true;
			}
			if (x >= 440 && x <= 725 && y >= 485 && y <= 545) {
				_isStartScreen = true;
				gameManager->startGame(_settingScreen->getNumPlayers());
			}
		}
	}
	
	void ScreenManager::onReshape(int width, int height)
	{
		_startScreen->onReshape(width, height);
		_settingScreen->onReshape(width, height);
	}
}