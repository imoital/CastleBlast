//
//  Loader.cpp
//  Project
//
//  Created by Inês on 10/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Loader.h"

namespace CastleBlast {
	
	GLuint Loader::loadTexture(const char *filename) {
		
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib(0);
		BYTE* bits(0);
		GLuint gl_texID;
		unsigned int width(0), height(0);
		
		fif = FreeImage_GetFileType(filename, 0);
		if(fif == FIF_UNKNOWN) {
			fif = FreeImage_GetFIFFromFilename(filename);
			return 0;
		}
		
		if(FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		if(!dib)
			return false;
		
		dib = FreeImage_ConvertTo24Bits(dib);
		bits = FreeImage_GetBits(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		if((bits == 0) || (width == 0) || (height == 0))
			return 0;
		
		glGenTextures(1, &gl_texID);
		glBindTexture(GL_TEXTURE_2D, gl_texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, bits);
		// FreeImage loads textures in BGR format.
		
		FreeImage_Unload(dib);
		
		return gl_texID;
	}
	
	std::vector<std::vector<int> > Loader::createHeightMap(const char* filename, int maxHeight)
	{
		RGBQUAD color;
		int width, height;
		FIBITMAP *image = FreeImage_Load(FIF_PNG, filename, PNG_DEFAULT);
		
		width = FreeImage_GetWidth(image);
		height = FreeImage_GetHeight(image);
		
		std::vector<std::vector<int> > map;
		
		for (int i = 0;  i < width; i++) {
			std::vector<int> a;
			map.push_back(a);
			for (int j = 0; j < height; j++){
				FreeImage_GetPixelColor(image, i, j, &color);
				float rgbRed = 1 - (float)color.rgbRed/(float)255;
				int depth = rgbRed*maxHeight;
				map[i].push_back(depth);
			}
			std::cout << std::endl;
			
		}
		
		return map;
	}
	

}