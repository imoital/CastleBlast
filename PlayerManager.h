//
//  PlayerManager.h
//  Project
//
//  Created by Inês on 11/14/11.
//  Copyright 2011 AVT. All rights reserved.
//

#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H
#include "cg/cg.h"

namespace CastleBlast {
	
	class Player;
	class FontsManager;
	
	class PlayerManager : public cg::Group, public cg::GroupDraw, public cg::GroupUpdate, public cg::GroupMouseEvent 
	{
	private:
		std::vector<Player*> _players;
		float _distancePlayers; //distance from witch player
		int _currentPlayerNum;
		Player* _currentPlayer;
		FontsManager* _fontsManager;
		bool _changePlayerPressed;
		int _numPlayers;
		bool _isGameOver;
		float anim;
		bool auxAnim;
		
	public:
		PlayerManager();
		~PlayerManager();
		
		void createEntities();
		void preInit();
		void postInit();
		void draw();
		void update(unsigned long elapsed_millis);
		void onMouse(int button, int state, int x, int y);
		void onMouseMotion(int x, int y);
		void onMousePassiveMotion(int x, int y);
		Player* nextPlayer();
		void setNumPlayers(int numPlayers);
		bool getIsOtherPlayer();
		bool finishGame();
		Player* winnerPlayer();
	};
}

#endif