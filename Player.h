//
//  Player.h
//  Project
//
//  Created by Inês on 11/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "cg/cg.h"

namespace CastleBlast {
	
	// prevent cicles in include classes. The includes are in the .cpp file
	class King;
	class Cannon;
	class CameraManager;
	class WorldCamera;
	class GameManager;
	
	// se aqui eu tirar cg::IMouseEventListener e puser cg::GroupMouseEvent CRASHA!
	class Player : 
	public cg::Group, 
	public cg::GroupDraw, 
	public cg::GroupUpdate, 
	public cg::GroupMouseEvent,
	public cg::IReshapeEventListener
	{
		
	private:
		King* _king;
		GameManager* _gameManager;
		Cannon* _cannon;
		CameraManager* _cameraManager;
		WorldCamera * _worldCamera;
		int _playerNumber;
		bool _currentPlayer;
		bool _changeCameraKeyPressed;
		float _playerRot;
		
	public:
		Player(std::string id, int number, WorldCamera * w, GameManager* gm);
		~Player();
		
		void postInit();
		void createEntities();
		cg::Vector3d getCannonPosition();
		void postUpdate(unsigned long elapsed_millis);
		void positionKing(cg::Vector3d initPosition);
		void positionCannon(cg::Vector3d initPosition);
		void drawCamera();
		void setCurrentPlayer();
		void unsetCurrentPlayer();
		int getPlayerNumber();
		bool isKingAlive();
		CameraManager* getCamera();
		void setWorldCamera(WorldCamera* w);
		void setRotation(float rotation);
		void onReshape(int witdth, int height);
	};
}

#endif