//
//  FontsManager.h
//  Project
//
//  Created by Inês on 11/19/11.
//  Copyright 2011 AVT. All rights reserved.
//

#ifndef FONTS_MANAGER_H
#define FONTS_MANAGER_H

#include <cg/cg.h>

namespace CastleBlast {
	
	class FontsManager : public cg::Entity {
		
	private:
		std::vector<GLuint> _textureFonts;
		std::vector<GLuint> _bases;
		
	public:
		FontsManager();
		~FontsManager();
		
		void init();
		void GLBuildFonts();
		void printFont(int x, int y, float size, int set, int fontId, std::string text);
		
	};
}

#endif