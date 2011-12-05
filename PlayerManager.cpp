//
//  PlayerManager.cpp
//  Project
//
//  Created by Inês on 11/14/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include "PlayerManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "GameManager.h"
#include <math.h>

namespace CastleBlast {
	
	PlayerManager::PlayerManager() : cg::Group("PLAYER_MANAGER") {}
	
	PlayerManager::~PlayerManager() {}
	
	void PlayerManager::preInit()
	{
		_distancePlayers = 2*3.14 / (double) cg::Properties::instance()->getInt("NUM_PLAYERS");
		_currentPlayerNum = 0;

	}
	
	void PlayerManager::createEntities()
	{
		int numPlayers = cg::Properties::instance()->getInt("NUM_PLAYERS");
		
		for (int i = 0; i < numPlayers; i++) {
			std::ostringstream player;
			player << "PLAYER" << i;
			Player* p = new Player(player.str(), i+1);
			_players.push_back(p);
			addAtBeginning(p);
		}
	}
	
	void PlayerManager::postInit()
	{
		int relativePos=20; //this test is a stupid hack to make cannons face each other. We most program quickly as evaluation is comming!!!
		int rot= 180;
		cg::Vector2d distanceCenter = cg::Vector2d (50, 50); //player distance from center
		GameManager* gameManager = (GameManager*)cg::Registry::instance()->get("GAME_MANAGER");
		SceneManager* sceneManager = (SceneManager*)gameManager->get("SCENE_MANAGER");
		int worldsize = sceneManager->getWorldSize();
		int center = worldsize/2;
		std::vector<cg::Vector2d> playerPos;
		
		for (int i = 0; i < size(); i++) {
			playerPos.push_back(cg::Vector2d(center - 20 + (int)distanceCenter[0]*sin(_distancePlayers*i), 
							 center + (int)distanceCenter[1]*cos(_distancePlayers*i)));
			sceneManager->placeCastle(playerPos[i][0], playerPos[i][1]);
		}
		
		for (int i = 0; i < size(); i++) {
			cg::Vector3d kingPos = sceneManager->getWorldPosition(playerPos[i][0]+14, playerPos[i][1]+15);
			cg::Vector3d cannonPos = sceneManager->getWorldPosition(playerPos[i][0]+4+relativePos, playerPos[i][1]+24-relativePos);
			_players[i]->positionKing(kingPos);
			_players[i]->positionCannon(cannonPos, rot);
			relativePos -=20;
			rot -= 180;
		}
		_currentPlayer = _players[0];
		_currentPlayer->setCurrentPlayer();
	}
	
	Player* PlayerManager::nextPlayer()
	{
		int numPlayers = cg::Properties::instance()->getInt("NUM_PLAYERS");
		Player* p = _players[_currentPlayerNum];
		_currentPlayer->unsetCurrentPlayer();
		_currentPlayer = p;
		_currentPlayer->setCurrentPlayer();
		_currentPlayerNum = (_currentPlayerNum+1)%numPlayers;
		return p;
	}
	
	// Need to be uncommented when camera manager is finish (need to be where for change players to work)
	void PlayerManager::update(unsigned long elapsed_millis)
	{
		_currentPlayer->update(elapsed_millis);
	}
	
	void PlayerManager::onMouse(int button, int state, int x, int y)
	{
		_currentPlayer->onMouse(button, state, x, y);
	}
	
	void PlayerManager::onMouseMotion(int x, int y)
	{
		_currentPlayer->onMouseMotion(x, y);
	}
	
	void PlayerManager::onMousePassiveMotion(int x, int y)
	{
		_currentPlayer->onMousePassiveMotion(x, y);
	}
	
	void PlayerManager::draw()
	{
		int numPlayers = cg::Properties::instance()->getInt("NUM_PLAYERS");
		
		for (int i = _players.size(); i >= 0; i--) {
			_players[(i+_currentPlayerNum)%numPlayers]->draw();
		}
	}
}
