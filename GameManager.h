//
//  GameManager.h
//  Project
//
//  Created by Inês on 11/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "cg/cg.h"

namespace CastleBlast {
	
	class SceneManager;
	class PlayerManager;
	class Player;
	class FontsManager;
	
	class GameManager : public cg::Group, public cg::GroupDraw, public cg::GroupUpdate, public cg::GroupMouseEvent{
	private:
		SceneManager* _sceneManager;
		PlayerManager* _playerManager;
		Player* _currentPlayer;
		FontsManager* _fontsManager;
		bool _changePlayerPressed;
		GLuint _fontTexture;
		GLuint _base;
		
	public:
		GameManager();
		~GameManager();
		
		void preInit();
		void postInit();
		void createEntities();
		void preDrawOverlay();
		void preUpdate(unsigned long elapsed_millis);
	};
}

#endif