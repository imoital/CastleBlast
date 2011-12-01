//
//  PlayerManager.h
//  Project
//
//  Created by Inês on 11/14/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include "cg/cg.h"

namespace CastleBlast {
	
	class Player;
	
	class PlayerManager : public cg::Group, public cg::GroupDraw, public cg::GroupUpdate, public cg::GroupMouseEvent 
	{
	private:
		std::vector<Player*> _players;
		float _distancePlayers; //distance from witch player
		int _currentPlayer;
		
	public:
		PlayerManager();
		~PlayerManager();
		
		void createEntities();
		void preInit();
		void postInit();
		Player* nextPlayer();
	};
}