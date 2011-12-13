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


namespace CastleBlast {
	
	GameManager::GameManager(int level) : Group("GAME_MANAGER") 
	{
		_currentLevel = level;
	}
	
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
	}
	
	void GameManager::postInit()
	{
		_currentPlayer = _playerManager->nextPlayer();
		removeAll();
		addAtBeginning(_screenManager);
		_lights->setLevel(_currentLevel);
		_sky->setLevel(_currentLevel);
		_fog->setLevel(_currentLevel);

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
				endGame();
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

		}

		_fog->draw(); //this stupid hack shouldn't be needed! This class should draw all it's entities! 
	}

	void GameManager::changePlayer()
	{
		std::cout << "is changing player" << std::endl;
		_currentPlayer = _playerManager->nextPlayer();
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
		_playerManager->setNumPlayers(numPlayers);
		_sceneManager->restart();
		_playerManager->restart();
	}
	
	void GameManager::endGame()
	{
		_gameMode = false;
		_playerManager->setNumPlayers(2);
		removeAll();
		addAtBeginning(_screenManager);
	}
}