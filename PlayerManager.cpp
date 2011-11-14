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
#include <math.h>

namespace CastleBlast {
	
	PlayerManager::PlayerManager() : cg::Group("PLAYER_MANAGER") {}
	
	PlayerManager::~PlayerManager() {}
	
	void PlayerManager::preInit()
	{
		_distancePlayers = 2*3.14 / (double) cg::Properties::instance()->getInt("NUM_PLAYERS");

	}
	
	void PlayerManager::createEntities()
	{
		int numPlayers = cg::Properties::instance()->getInt("NUM_PLAYERS");
		
		for (int i = 0; i < numPlayers; i++) {
			std::ostringstream player;
			player << "PLAYER" << i;
			Player* p = new Player(player.str());
			_players.push_back(p);
			addAtBeginning(p);
		}
	}
	
	void PlayerManager::postInit()
	{
		cg::Vector2d distanceCenter = cg::Vector2d (50, 50); //player distance from center
		SceneManager* sceneManager = (SceneManager*)cg::Registry::instance()->get("SCENE_MANAGER");
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
			cg::Vector3d cannonPos = sceneManager->getWorldPosition(playerPos[i][0]+4, playerPos[i][1]+25);
			_players[i]->positionKing(kingPos);
			_players[i]->positionCannon(cannonPos);
		}
	}
}
