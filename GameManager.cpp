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

namespace CastleBlast {
	
	GameManager::GameManager() : Group("GAME_MANAGER") {}
	
	GameManager::~GameManager() {}
	
	void GameManager::preInit()
	{
		_sceneManager = new SceneManager();
		_playerManager = new PlayerManager();
		_changePlayerPressed = false;
		_fontsManager = (FontsManager*)cg::Registry::instance()->get("FONTS_MANAGER");
		_screenManager = new ScreenManager();
		_sky = new Sky();
		_birdsManager = new BirdsManager();
		_gameMode = false;
		_isEndGame = false;
	}
	
	void GameManager::createEntities()
	{	
		addAtBeginning(_sceneManager);
		addAtBeginning(_playerManager);
		addAtBeginning(_sky);
		//addAtBeginning(new CameraManager());
		addAtBeginning(_screenManager);
		addAtBeginning(_birdsManager);
	}
	
	void GameManager::postInit()
	{
		_currentPlayer = _playerManager->nextPlayer();
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
				_fontsManager->printFont(100, 300, 2, 0, 1, winnerPlayer.str());
			}
		}
	}
	
	void GameManager::preUpdate(unsigned long elapsed_millis)
	{
		if (_gameMode) {
			if(cg::KeyBuffer::instance()->isKeyDown('z') && !_changePlayerPressed) {
				_currentPlayer = _playerManager->nextPlayer();
				_changePlayerPressed = true;
			}
			if (cg::KeyBuffer::instance()->isKeyUp('z') && _changePlayerPressed) {
				_changePlayerPressed = false;
			}

			if (_playerManager->getIsOtherPlayer() == true)
				_currentPlayer = _playerManager->nextPlayer();
		}
	}
	
	void GameManager::postUpdate(unsigned long elapsed_millis)
	{
	}
	
	void GameManager::preOnMouse(int button, int state, int x, int y) 
	{
		if (!_gameMode) {
			if(x >= 265 && x <= 555 && y >= 270 && y <= 330)
				startGame(2);
		}
	}
	
	void GameManager::startGame(int numPlayers) 
	{
		_gameMode = true;

		removeAll();
		addAtBeginning(_sky);
		addAtBeginning(_sceneManager);
		addAtBeginning(_birdsManager);
		addAtBeginning(_playerManager);
	}
	
	void GameManager::endGame()
	{
		removeAll();
		_gameMode = false;
		addAtBeginning(_screenManager);
	}
}