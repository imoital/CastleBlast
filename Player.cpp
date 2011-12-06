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
		_changeCameraKeyPressed = false;
	}
	
	void Player::positionKing(cg::Vector3d initPosition)
	{
		_king->placeKing(initPosition);
	}
	
	void Player::positionCannon(cg::Vector3d initPosition, int rot)
	{
		_cannon->placeCannon(initPosition, rot);
		_cameraManager->setCannonCameraRotation(rot);
	}

	
	int Player::getPlayerNumber()
	{
		return _playerNumber;
	}

	bool Player::getIsOtherPlayer()
	{
		return _cannon->getIsOtherPlayer();
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
	
	void Player::postUpdate(unsigned long elapsed_millis)
	{
		if(cg::KeyBuffer::instance()->isKeyDown('c') && !_changeCameraKeyPressed) {
			_cameraManager->switchCamera();
			_cannon->cameraToggle();
			_changeCameraKeyPressed = true;
		}
		if (cg::KeyBuffer::instance()->isKeyUp('c') && _changeCameraKeyPressed) {
			_changeCameraKeyPressed = false;
		}
	}
}