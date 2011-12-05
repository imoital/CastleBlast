//
//  Player.cpp
//  Project
//
//  Created by Inês on 11/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Player.h"
#include "King.h"
#include "Cannon.h"
#include "CameraManager.h"
namespace CastleBlast {
	
	Player::Player(std::string id, int number) : cg::Group(id)
	{
		_playerNumber = number;
		_currentPlayer = false;
	}
	
	Player::~Player() {}
	
	
	void Player::createEntities() 
	{
		_king = new King();
		_cannon = new Cannon();
		_cameraManager = new CameraManager(_cannon);
		
		addAtBeginning(_king);
		addAtBeginning(_cannon);
		addAtBeginning(_cameraManager);
	}
	
	void Player::postInit()
	{
		remove("CAMERA_MANAGER");
	}
	
	void Player::positionKing(cg::Vector3d initPosition)
	{
		_king->placeKing(initPosition);
	}
	
	void Player::positionCannon(cg::Vector3d initPosition)
	{
		_cannon->placeCannon(initPosition);
	}
	
	int Player::getPlayerNumber()
	{
		return _playerNumber;
	}
	
	void Player::setCurrentPlayer()
	{
		addAtBeginning(_cameraManager);
	}
	void Player::unsetCurrentPlayer()
	{
		remove("CAMERA_MANAGER");
	}
	
	void Player::drawCamera()
	{
		_cameraManager->draw();
	}
}