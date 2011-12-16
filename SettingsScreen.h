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
		GLuint _settingsScreen_selectMapDay;
		GLuint _settingsScreen_night;
		GLuint _settingsScreen_backNight;
		GLuint _settingsScreen_startNight;
		GLuint _settingsScreen_selectMapNight;
		GLuint _settingsScreen_select1;
		GLuint _settingsScreen_select1Back;
		GLuint _settingsScreen_select2;
		GLuint _settingsScreen_select2Back;
		GLuint _settingsScreen_select3;
		GLuint _settingsScreen_select3Back;
		
		FontsManager* _fontsManager;
		int _width;
		int _height;
		bool _selectMap, _enterSelectMap, _ambient, _start, _back, _day, _downPressed, _upPressed, _rightPressed, _leftPressed, _mapBack;
		int _mapNum;
		
	public:
		SettingsScreen();
		~SettingsScreen();
		
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		int getNumMap();
		void onReshape(int witdth, int height);
		bool isDay();
		bool isStart();
		bool isBack();
		bool isSelectMap();
		bool isMapBack();
		void gotoSelectMap();
		void gotoSettings();
	};
}

#endif