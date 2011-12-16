//
//  GameManager.cpp
//  Project
//
//  Created by Inês on 11/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GameManager.h"
#include "Player.h"
#include "ModelManager.h"
#include "PlayerManager.h"
#include "FontsManager.h"
#include "SceneManager.h"
#include "ScreenManager.h"
#include "Sky.h"
#include "BirdsManager.h"
#include "Lights.h"
#include "Fog.h"
#include "Wind.h"

namespace CastleBlast {
	
	GameManager::GameManager() : Group("GAME_MANAGER") {}
	
	GameManager::~GameManager() {}
	
	void GameManager::preInit()
	{
		_sceneManager = new SceneManager();
		_playerManager = new PlayerManager(this);
		_changePlayerPressed = false;
		_fontsManager = (FontsManager*)cg::Registry::instance()->get("FONTS_MANAGER");
		_screenManager = new ScreenManager();
		_sky = new Sky();
		_birdsManager = new BirdsManager();
		_gameMode = false;
		_isEndGame = false;
		_lights = new Lights();
		_fog = new Fog();
		_wind = new Wind();
	}
	
	void GameManager::createEntities()
	{	
		addAtBeginning(_sceneManager);
		addAtBeginning(_playerManager);
		addAtBeginning(_sky);
		addAtBeginning(_screenManager);
		addAtBeginning(_birdsManager);
		addAtBeginning(_lights);
		addAtBeginning(_fog);
		addAtBeginning(_wind);
	}
	
	void GameManager::postInit()
	{
		removeAll();
		addAtBeginning(_screenManager);

	}
	
	void GameManager::preDrawOverlay()
	{
		if (_gameMode) {
			std::stringstream player;
			player << "Player " << _currentPlayer->getPlayerNumber() << " turn";
			
			_fontsManager->printFont(10, 10,1, 0, 1, player.str());
			
			if (_playerManager->finishGame()) {
				std::stringstream winnerPlayer;
				winnerPlayer << "Player " << _playerManager->winnerPlayer()->getPlayerNumber() << " is the winner";
				cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
				_fontsManager->printFont(win.width/2.0-win.width/2.6, win.height/2.0, 2, 0, 1, winnerPlayer.str());
				_fontsManager->printFont(win.width/2.0-win.width/2.3, win.height/2.0-win.width/20.0, 2, 0, 1, "Press \"enter\" to continue");
				_isEndGame = true;
			}
		}
	}
	
	void GameManager::preUpdate(unsigned long elapsed_millis)
	{
		if (_gameMode) {
			if(cg::KeyBuffer::instance()->isKeyDown('z') && !_changePlayerPressed) {
				changePlayer();
				_changePlayerPressed = true;
			}
			if (cg::KeyBuffer::instance()->isKeyUp('z') && _changePlayerPressed) {
				_changePlayerPressed = false;
			}
			if (cg::KeyBuffer::instance()->isKeyDown(GLUT_KEY_RETURN) && _isEndGame) {
				endGame();
			}
		}
	}

	void GameManager::changePlayer()
	{
		_currentPlayer = _playerManager->nextPlayer();
	}
	
	void GameManager::postUpdate(unsigned long elapsed_millis)
	{
	}
	
	void GameManager::preOnMouse(int button, int state, int x, int y) 
	{
	}
	
	void GameManager::startGame(int mapNumber, int ambient) 
	{
		_isEndGame = false;
		
		removeAll();
		addAtBeginning(_sky);
		addAtBeginning(_sceneManager);
		if (ambient == DAY)
			addAtBeginning(_birdsManager);
		addAtBeginning(_playerManager);
		addAtBeginning(_fog);
		addAtBeginning(_wind);
		_currentAmbient = ambient;
		_sceneManager->setTerrain(mapNumber);
		_lights->setLevel(_currentAmbient);
		_sky->setLevel(_currentAmbient);
		_fog->setLevel(_currentAmbient);
		_playerManager->setNumPlayers(2);
		_sceneManager->restart();
		_playerManager->restart();
		_currentPlayer = _playerManager->nextPlayer();
		_gameMode = true;
	}
	
	void GameManager::endGame()
	{
		_gameMode = false;
		_isEndGame = false;
		_playerManager->setNumPlayers(2);
		removeAll();
		_screenManager->restart();
		addAtBeginning(_screenManager);
	}
	
	void GameManager::onReshape(int width, int height)
	{
		_playerManager->onReshape(width, height);
		_screenManager->onReshape(width, height);
	}
}