//
//  SettingsScreen.h
//  CastleBlast
//
//  Created by Inês on 12/5/11.
//  Copyright 2011 AVT. All rights reserved.
//

#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H

#include <cg/cg.h>

namespace CastleBlast {
	
	class FontsManager;
	
	class SettingsScreen {
	private:
		
		GLuint _settingsScreen_day;
		GLuint _settingsScreen_backDay;
		GLuint _settingsScreen_startDay;
		GLuint _settingsScreen_playersDay;
		GLuint _settingsScreen_night;
		GLuint _settingsScreen_backNight;
		GLuint _settingsScreen_startNight;
		GLuint _settingsScreen_playersNight;
		
		FontsManager* _fontsManager;
		int _numPlayers;
		int _width;
		int _height;
		bool _players, _ambient, _start, _back, _day, _downPressed, _upPressed, _rightPressed, _leftPressed;
		
	public:
		SettingsScreen();
		~SettingsScreen();
		
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		int getNumPlayers();
		void onReshape(int witdth, int height);
		bool isDay();
		bool isStart();
		bool isBack();
	};
}

#endif