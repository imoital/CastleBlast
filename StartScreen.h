//
//  StartScreen.h
//  CastleBlast
//
//  Created by Inês on 12/4/11.
//  Copyright 2011 AVT. All rights reserved.
//

#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <cg/cg.h>

namespace CastleBlast {
	class StartScreen {
	private:
		
		GLuint _startScreenImage;
		GLuint _settingsScreenImage;
		int _width;
		int _height;
		bool _start;
	public:
		StartScreen();
		~StartScreen();
		
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		void onReshape(int witdth, int height);
		bool isStart();
		void restart();
	};
}

#endif