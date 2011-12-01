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

namespace CastleBlast {
	
	Player::Player(std::string id, int number) : cg::Group(id)
	{
		_playerNumber = number;
	}
	
	Player::~Player() {}
	
	
	void Player::createEntities() 
	{
		_king = new King();
		_cannon = new Cannon();
		
		addAtBeginning(_king);
		addAtBeginning(_cannon);
		addAtBeginning(new CameraManager());
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
}