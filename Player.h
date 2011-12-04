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
										// se aqui eu tirar cg::IMouseEventListener e puser cg::GroupMouseEvent CRASHA!
	class Player : public cg::Group, public cg::GroupDraw, public cg::GroupUpdate, public cg::GroupMouseEvent
	{
		
	private:
		King* _king;
		Cannon* _cannon;
		int _playerNumber;
		bool _currentPlayer;
		
	public:
		Player(std::string id, int number);
		~Player();
		
		void createEntities();
		void positionKing(cg::Vector3d initPosition);
		void positionCannon(cg::Vector3d initPosition);
		void setCurrentPlayer();
		void unsetCurrentPlayer();
		int getPlayerNumber();
	};
}

#endif