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
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
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
			
		}
		
		return map;
	}
	
	GLuint Loader::buildFont(GLuint fontTexture)
	{
		float cx;
		float cy;
		
		GLuint base = glGenLists(256);

		glBindTexture(GL_TEXTURE_2D, fontTexture);
		
		glPushMatrix();
		for (int loop = 0; loop < 256; loop++){
			cx=float(loop%16)/16.0f;                    // X Position Of Current Character
			cy=float(loop/16)/16.0f;                    // Y Position Of Current Character
			
			glNewList(base+loop,GL_COMPILE);                // Start Building A List
			{
				glBegin(GL_QUADS);                  // Use A Quad For Each Character
				{
					glTexCoord2f(cx,1-cy-0.0625f);          // Texture Coord (Bottom Left)
					glVertex2i(0,0);			// Vertex Coord (Bottom Left)
					glTexCoord2f(cx+0.0625f,1-cy-0.0625f);		// Texture Coord (Bottom Right)
					glVertex2i(16,0);				// Vertex Coord (Bottom Right)
					glTexCoord2f(cx+0.0625f,1-cy);          // Texture Coord (Top Right)
					glVertex2i(16,16);			// Vertex Coord (Top Right)
					glTexCoord2f(cx,1-cy);          // Texture Coord (Top Left)
					glVertex2i(0,16);		// Vertex Coord (Top Left)
				}
				glEnd();
				glTranslated(13,0,0);                   // Move To The Right Of The Character
			}
			glEndList();                            // Done Building The Display List
		}
		glPopMatrix();
		
		return base;
	}
	
	void Loader::killFont(GLuint base)
	{
		glDeleteLists(base,256);                        // Delete All 256 Display Lists
	}
	
	GLvoid Loader::printFont(GLint x, GLint y, float size, const char *string, int set, GLuint fontTexture, GLuint base)
	{
		if (set>1)                               // Is set Greater Than One?
		{
			set=1;                              // If So, Make Set Equal One
		}
		
		glBindTexture(GL_TEXTURE_2D, fontTexture);
		
		glDisable(GL_DEPTH_TEST);                       // Disables Depth Testing
		
		glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
		glPushMatrix();                             // Store The Projection Matrix
		glLoadIdentity();                           // Reset The Projection Matrix
		glOrtho(0,1000,0,800,-1,1);                      // Set Up An Ortho Screen
		
		glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
		glPushMatrix();                             // Store The Modelview Matrix
		glLoadIdentity();                           // Reset The Modelview Matrix
		
		glEnable(GL_TEXTURE_2D);
		glTranslated(x,y,0);                            // Position The Text (0,0 - Bottom Left)
		glScaled(size, size, size);
		glListBase(base-32+(128*set));                      // Choose The Font Set (0 or 1)
		glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);            // Write The Text To The Screen
		glDisable(GL_TEXTURE_2D);

		glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
		glPopMatrix();                              // Restore The Old Projection Matrix
		
		glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
		glPopMatrix();                              // Restore The Old Projection Matrix
		
		glEnable(GL_DEPTH_TEST);
	}

}