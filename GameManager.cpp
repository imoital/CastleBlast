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
	}
	
	void GameManager::startGame(int numPlayers, int ambient) 
	{
		_gameMode = true;

		removeAll();
		addAtBeginning(_sky);
		addAtBeginning(_sceneManager);
		addAtBeginning(_birdsManager);
		addAtBeginning(_playerManager);
		addAtBeginning(_fog);
		addAtBeginning(_wind);
		_currentAmbient = ambient;
		_lights->setLevel(_currentAmbient);
		_sky->setLevel(_currentAmbient);
		_fog->setLevel(_currentAmbient);
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
	
	void GameManager::onReshape(int width, int height)
	{
		_playerManager->onReshape(width, height);
		_screenManager->onReshape(width, height);
	}
}