//
//  ScreenManager.h
//  CastleBlast
//
//  Created by Inês on 12/5/11.
//  Copyright 2011 AVT. All rights reserved.
//

#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <cg/cg.h>

#define GLUT_KEY_RETURN 13

namespace CastleBlast {
	
	class SettingsScreen;
	class StartScreen;
	
	class ScreenManager: 
	public cg::Entity, 
	public cg::IDrawListener, 
	public cg::IUpdateListener, 
	public cg::IMouseEventListener,
	public cg::IReshapeEventListener{
	private:
		SettingsScreen* _settingScreen;
		StartScreen* _startScreen;
		bool _isStartScreen;
		bool _isReturnPressed;
		
	public:
		ScreenManager();
		~ScreenManager();
		
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
		void onMouse(int button, int state, int x, int y);
		void onReshape(int width, int height);
	}; 
}


#endif