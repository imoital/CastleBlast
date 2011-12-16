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
#include "WorldCamera.h"
#include "GameManager.h"

namespace CastleBlast {
	
	Player::Player(std::string id, int number, GameManager* gm) : cg::Group(id)
	{
		_playerNumber = number;
		_currentPlayer = false;
		_playerRot = 0;
		_gameManager = gm;
	}
	
	Player::~Player() {}
	
	
	void Player::createEntities() 
	{
		_king = new King();
		_cannon = new Cannon(_gameManager);
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
	
	cg::Vector3d Player::getCannonPosition(){
		return _cannon->getPosition();
	}

	void Player::positionKing(cg::Vector3d initPosition)
	{
		_king->placeKing(initPosition, _playerRot);
	}
	
	void Player::positionCannon(cg::Vector3d initPosition)
	{
		_cannon->placeCannon(initPosition, _playerRot);
		_cameraManager->setCannonCameraRotation(_playerRot);
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
	
	bool Player::isKingAlive()
	{
		return _king->isAlive();
	}

	CameraManager* Player::getCamera(){
		return _cameraManager;
	}
	
	void Player::setRotation(float rotation)
	{
		if(rotation >= 3*PI/4 && rotation <= 5*PI/4) 
			_playerRot = 0;
		else if (rotation > 5*PI/4 && rotation <= 7*PI/4)
			_playerRot = PI/2;
		else if (rotation > 7*PI/4 && rotation <= 8*PI/4)
			_playerRot = PI;
		else if (rotation >= 0 && rotation <= PI/4)
			_playerRot = PI;
		else if (rotation > PI/4 && rotation < 3*PI/4)
			_playerRot = 3*PI/2;
	}
	
	void Player::onReshape(int witdth, int height)
	{
		_cameraManager->onReshape(witdth, height);
	}
	
	void Player::setLineColor(double r, double g, double b)
	{
		_cameraManager->setLineColor(r, g, b);
	}

}