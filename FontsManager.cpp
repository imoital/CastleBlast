//
//  FontsManager.cpp
//  Project
//
//  Created by Inês on 11/19/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include "FontsManager.h"
#include "Loader.h"
#include <dirent.h>

namespace CastleBlast {
	
	FontsManager::FontsManager() : cg::Entity("FONTS_MANAGER"){}
	
	FontsManager::~FontsManager() {}
	
	void FontsManager::init()
	{
		GLBuildFonts();
	}
	
	void FontsManager::GLBuildFonts()
	{
		DIR *dir;
		struct dirent *ent;

		std::string fontDir;
		std::string thisDir = ".";
		std::string preVDir = "..";
		std::string macThing = ".DS_Store"; // on mac this folder is created in every dicertory
		
#ifdef __APPLE__
		fontDir = "Fonts/";
#else
		fontDir = "..\\..\\src\\Fonts\\";
#endif
		dir = opendir(fontDir.c_str());
		
		if (dir != NULL) {
			
			ent = readdir(dir);
			
			// get all files in the directory
			for(int i = 0; ent != NULL; ent = readdir(dir), i++){
				
				if(thisDir.compare(ent->d_name) && preVDir.compare(ent->d_name) && macThing.compare(ent->d_name)){
					std::stringstream filename;
					filename << fontDir << ent->d_name;
					
					_textureFonts.push_back(Loader::loadTexture(filename.str().c_str()));
					_bases.push_back(Loader::buildFont(_textureFonts[i]));
				}
			}
			
			closedir (dir);
		}
		
	}
	
	void FontsManager::printFont(int x, int y,float size, int set, int fontId, std::string text)
	{
		Loader::printFont(x, y, size, text.c_str(), set, _textureFonts[fontId], _bases[fontId]);
	}
}