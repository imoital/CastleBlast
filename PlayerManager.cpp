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
#include "FontsManager.h"
#include <math.h>
#include "WorldCamera.h"
#include "CameraManager.h"

namespace CastleBlast {
	
	PlayerManager::PlayerManager(GameManager* gm) : cg::Group("PLAYER_MANAGER") 
	{
		_numPlayers = 2;
		_currentPlayer = NULL;
		_gameManager = gm;
	}
	
	PlayerManager::~PlayerManager() {}
	
	void PlayerManager::preInit()
	{
		_distancePlayers = 2*3.14 / (double)_numPlayers;
		_currentPlayerNum = 0;
		_changePlayerPressed = false;
		_isGameOver = false;
		anim = 0;
		auxAnim = false;
		_isRestarting = false;

	}
	
	void PlayerManager::createEntities()
	{
		WorldCamera * _worldCamera = new WorldCamera();
		for (int i = 0; i < _numPlayers; i++) {
			std::ostringstream player;
			player << "PLAYER" << i;
			Player* p = new Player(player.str(), i+1, _worldCamera, _gameManager);
			_players.push_back(p);
			addAtBeginning(p);
		}
	}
	
	void PlayerManager::postInit()
	{
		int relativePos=20; //this test is a stupid hack to make cannons face each other. We most program quickly as evaluation is comming!!!
		int rot= 180;
		int distanceCenterX = cg::Properties::instance()->getInt("PLAYERS_DISTANCE_CENTER_X");
		int distanceCenterY = cg::Properties::instance()->getInt("PLAYERS_DISTANCE_CENTER_Y");
		cg::Vector2d distanceCenter = cg::Vector2d (distanceCenterX, distanceCenterY); //player distance from center
		GameManager* gameManager = (GameManager*)cg::Registry::instance()->get("GAME_MANAGER");
		SceneManager* sceneManager = (SceneManager*)gameManager->get("SCENE_MANAGER");
		_fontsManager = (FontsManager*)gameManager->get("FONTS_MANAGER");
		int worldsize = sceneManager->getWorldSize();
		int center = worldsize/2;
		std::vector<cg::Vector2d> playerPos;
		
		for (int i = 0; i < size(); i++) {
			playerPos.push_back(cg::Vector2d(center + (int)distanceCenter[0]*sin(_distancePlayers*i), 
							 center + (int)distanceCenter[1]*cos(_distancePlayers*i)));
			sceneManager->placeCastle(playerPos[i][0], playerPos[i][1]);
		}
		
		for (int i = 0; i < size(); i++) {
			_players[i]->setRotation(_distancePlayers*i);
			cg::Vector3d kingPos = sceneManager->getWorldPosition(playerPos[i][0]+14, playerPos[i][1]+15);
			cg::Vector3d cannonPos = sceneManager->getWorldPosition(playerPos[i][0]+4, playerPos[i][1]+24);
			_players[i]->positionKing(kingPos);
			_players[i]->positionCannon(cannonPos);
			relativePos -=20;
			rot -= 180;
		}
		_currentPlayer = _players[0];
		_currentPlayer->setCurrentPlayer();
	}
	
	Player* PlayerManager::nextPlayer()
	{
	//	WorldCamera* te;
		Player* p = _players[_currentPlayerNum];
	//	te = _currentPlayer->getCamera()->getWorldCamera();
		_currentPlayer->unsetCurrentPlayer();
		_currentPlayer = p;
		_currentPlayer->setCurrentPlayer();
		_currentPlayerNum = (_currentPlayerNum+1)%_numPlayers;
	//	p->setWorldCamera(te);
		if(!p->getCamera()->isWorldCamera()){
			p->getCamera()->switchCamera();
			p->getCamera()->getCannon()->cameraToggle();
		}
		return p;
	}
	
	// Need to be uncommented when camera manager is finish (need to be where for change players to work)
	void PlayerManager::update(unsigned long elapsed_millis)
	{
		if(!_isGameOver)
			_currentPlayer->update(elapsed_millis);
		if(anim > 2)
			auxAnim = true;
		if (anim < -2)
			auxAnim = false;
		if(auxAnim)
			anim -= elapsed_millis * 0.002;
		else
			anim += elapsed_millis * 0.002;

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
		for (int i = _players.size(); i >= 0; i--) {
			_players[(i+_currentPlayerNum)%_numPlayers]->draw();
		}
				//setinha
		cg::Vector3d pos = _currentPlayer->getCannonPosition();
		glPushMatrix();
		glShadeModel(GL_SMOOTH);
		glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLE_FAN);
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(pos[0], pos[1] + 10 + anim, pos[2]);
			glColor3f(1.0f, 0.5f, 0.0f);
			glVertex3f(pos[0]+ 1, pos[1] + 15 + anim, pos[2] + 1);
			glVertex3f(pos[0]+ 1, pos[1] + 15 + anim, pos[2] - 1);
			glVertex3f(pos[0]- 1, pos[1] + 15 + anim, pos[2] - 1);
			glVertex3f(pos[0]- 1, pos[1] + 15 + anim, pos[2] + 1);
			glVertex3f(pos[0]+ 1, pos[1] + 15 + anim, pos[2] + 1);
		}
		glEnd(); 
		glPopMatrix();
		glEnable(GL_LIGHTING);

	}
	
	void PlayerManager::setNumPlayers(int numPlayers)
	{
		_numPlayers = numPlayers;
	}
	
	bool PlayerManager::finishGame()
	{
		if(!_isRestarting) {
			for (int i = 0; i < _players.size(); i++) {
				if(!_players[i]->isKingAlive())
					return true;
			}
		}
		return false;
	}
	
	Player *PlayerManager::winnerPlayer()
	{
		for (int i = 0; i < _players.size(); i++) {
			if(_players[i]->isKingAlive())
				return _players[i];
		}
		return _players[0];
	}
	
	void PlayerManager::restart()
	{
		_isRestarting = true;
		_currentPlayer->unsetCurrentPlayer();
		_distancePlayers = 2*3.14 / (double)_numPlayers;
		_changePlayerPressed = false;
		_isGameOver = false;
		anim = 0;
		auxAnim = false;
		removeAll();
		_players.clear();
		WorldCamera * _worldCamera = new WorldCamera();
		for (int i = 0; i < _numPlayers; i++) {
			std::ostringstream player;
			player << "PLAYER" << i;
			Player* p = new Player(player.str(), i+1, _worldCamera, _gameManager);
			_players.push_back(p);
			addAtBeginning(p);
			p->init();
		}

		int distanceCenterX = cg::Properties::instance()->getInt("PLAYERS_DISTANCE_CENTER_X");
		int distanceCenterY = cg::Properties::instance()->getInt("PLAYERS_DISTANCE_CENTER_Y");
		cg::Vector2d distanceCenter = cg::Vector2d (distanceCenterX, distanceCenterY); //player distance from center
		GameManager* gameManager = (GameManager*)cg::Registry::instance()->get("GAME_MANAGER");
		SceneManager* sceneManager = (SceneManager*)gameManager->get("SCENE_MANAGER");
		int worldsize = sceneManager->getWorldSize();
		int center = worldsize/2;
		std::vector<cg::Vector2d> playerPos;
		
		for (int i = 0; i < size(); i++) {
			playerPos.push_back(cg::Vector2d(center + (int)distanceCenter[0]*sin(_distancePlayers*i), 
							 center + (int)distanceCenter[1]*cos(_distancePlayers*i)));
			sceneManager->placeCastle(playerPos[i][0], playerPos[i][1]);
		}
		
		for (int i = 0; i < size(); i++) {
			_players[i]->setRotation(_distancePlayers*i);
			cg::Vector3d kingPos = sceneManager->getWorldPosition(playerPos[i][0]+14, playerPos[i][1]+15);
			cg::Vector3d cannonPos = sceneManager->getWorldPosition(playerPos[i][0]+4, playerPos[i][1]+24);
			_players[i]->positionKing(kingPos);
			_players[i]->positionCannon(cannonPos);
		}
		
		_currentPlayer = _players[0];
		_currentPlayer->setCurrentPlayer();
		_isRestarting = false;
	}
}
