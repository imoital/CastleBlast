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

#define DAY 1
#define NIGHT 2

namespace CastleBlast {
	
	class SceneManager;
	class PlayerManager;
	class Player;
	class FontsManager;
	class ScreenManager;
	class Sky;
	class BirdsManager;
	class Lights;
	class Fog;

	class GameManager : 
	public cg::Group, 
	public cg::GroupDraw, 
	public cg::GroupUpdate, 
	public cg::GroupMouseEvent , 
	public cg::IReshapeEventListener
	{
		
	private:
		SceneManager* _sceneManager;
		PlayerManager* _playerManager;
		Player* _currentPlayer;
		FontsManager* _fontsManager;
		ScreenManager* _screenManager;
		Sky* _sky;
		Lights* _lights;
		BirdsManager* _birdsManager;
		Fog* _fog;
		int _currentAmbient;
		bool _changePlayerPressed;
		GLuint _fontTexture;
		GLuint _base;
		bool _gameMode;
		bool _isEndGame;
		
	public:
		GameManager();
		~GameManager();
		
		void preInit();
		void postInit();
		void createEntities();
		void preDrawOverlay();
		void preUpdate(unsigned long elapsed_millis);
		void postUpdate(unsigned long elapsed_millis);
		void preOnMouse(int button, int state, int x, int y);
		void startGame(int numPlayers, int ambient);
		void endGame();
		void changePlayer();
		void onReshape(int width, int height);
	};
}

#endif