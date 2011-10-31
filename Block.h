//
//  Block.h
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef BLOCK_H
#define BLOCK_H

#include "cg/cg.h"

namespace CastleBlast {
	
	// Block : abstract class that draws a block
	class Block {
	
	public:
		int _materialDL; //texture of the block
		
		Block();
		~Block();
		
		/* draw (int f, int bk, int l, int r, int t, int bt, cg::Vector3d matrixPos):
		 
			f = 1	-> draw front face
			bk = 1	-> draw back face
			l = 1 -> draw left face
			r = 1 -> draw right face
			t = 1 -> draw top face
			bt = 1 -> draw bottom face
			
			if any of the above variables is equal to 0 the face is not drawn
		 
			matrixPos is the position of the block in the world matrix
		 */
		void draw(int f, int bk, int l, int r, int t, int bt, int startLine, int endLine, int startColumn, int endColumn, int depth);
		
		// Needs to be implemented in the below classes to load a texture
		virtual int loadType() = 0;
		
		// returns the texture of the block
		int getTexture();
		
	private:
		int _blockSize;
		cg::Vector3d _startFrom; // where the first block will start to be drawn
		cg::Vector3d _startPoint; // where the block will start to be drawn
		cg::Vector3d _endPoint;
		
		void drawFrontFace(int lines, int columns);
		void drawBackFace(int lines, int columns);
		void drawLeftFace(int lines, int columns);
		void drawRightFace(int lines, int columns);
		void drawTopFace(int lines, int columns);
		void drawBottomFace(int lines, int columns);
		void makeTexture(int lines, int columns);
	};
}

#endif