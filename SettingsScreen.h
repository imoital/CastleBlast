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
		
		GLuint _settingsScreenImage;
		FontsManager* _fontsManager;
		int _numPlayers;
		
	public:
		SettingsScreen();
		~SettingsScreen();
		
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		int getNumPlayers();
	};
}

#endif