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
		int _topBottomTexture; //texture of the block
		int _sideTexture;
		
		Block(cg::Vector3d startFrom);
		~Block();
		
		// draws a cube from the start line ('startLine') to the endline('endLine'), 
		// from the start column ('startColumn') to the end column ('endColumn') and at depth 'depth'
		void draw(int startLine, int endLine, int startColumn, int endColumn, int depth);
		
		// Needs to be implemented in the below classes to load a texture
		virtual void loadTextures() = 0;
		
	protected:
		// materials for blocks
		GLfloat topBottom_mat_ambient[4];
		GLfloat topBottom_mat_difusse[4];
		GLfloat topBottom_mat_specular[4];
		GLfloat topBottom_shininess;
		
		GLfloat side_mat_ambient[4];
		GLfloat side_mat_difusse[4];
		GLfloat side_mat_specular[4];
		GLfloat side_shininess;
		
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