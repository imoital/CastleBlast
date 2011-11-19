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
#include "Loader.h"
#include "FontsManager.h"

namespace CastleBlast {
	
	GameManager::GameManager() : Group("GAME_MANAGER") {}
	
	GameManager::~GameManager() {}
	
	void GameManager::preInit()
	{
		_playerManager = new PlayerManager();
		_changePlayerPressed = false;
		_fontsManager = (FontsManager*)cg::Registry::instance()->get("FONTS_MANAGER");
		
	}
	
	void GameManager::createEntities()
	{		
		addAtBeginning(_playerManager);
	}
	
	void GameManager::postInit()
	{
		_currentPlayer = _playerManager->nextPlayer();
	}
	
	void GameManager::preDrawOverlay()
	{
		std::stringstream player;
		player << "Player " << _currentPlayer->getPlayerNumber();
		
		_fontsManager->printFont(10, 10,1, 0, 1, player.str());
	}
	
	void GameManager::preUpdate(unsigned long elapsed_millis)
	{
		if(cg::KeyBuffer::instance()->isKeyDown('z') && !_changePlayerPressed) {
			_currentPlayer = _playerManager->nextPlayer();
			_changePlayerPressed = true;
		}
		if (cg::KeyBuffer::instance()->isKeyUp('z') && _changePlayerPressed) {
			_changePlayerPressed = false;
		}
	}
}