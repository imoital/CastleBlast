//
//  GameManager.cpp
//  Project
//
//  Created by Inês on 11/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GameManager.h"
#include "Player.h"
#include "SceneManager.h"

namespace CastleBlast {
	
	GameManager::GameManager() : Group("GAME_MANAGER") {}
	
	GameManager::~GameManager() {}
	
	void GameManager::preInit()
	{
		_sceneManager = new SceneManager();
		_player1 = new Player("PLAYER1");
		
	}
	
	void GameManager::createEntities()
	{		
		addAtBeginning(_sceneManager);
		addAtBeginning(_player1);
	}
	
	void GameManager::postInit()
	{
		_sceneManager->placeCastle(160, 120);
		_sceneManager->placeCastle(160, 230);
		cg::Vector3d kingPosition = _sceneManager->getWorldPosition(174, 135);
		cg::Vector3d cannonPosition = _sceneManager->getWorldPosition(164, 145);
		_player1->positionKing(kingPosition);
		_player1->positionCannon(cannonPosition);
	}
}