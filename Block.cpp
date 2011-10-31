//
//  Block.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Block.h"

namespace CastleBlast {
	
	Block::Block() 
	{
		_blockSize = cg::Properties::instance()->getInt("BLOCK_SIZE");
		int wordlSize = cg::Properties::instance()->getInt("WORLD_SIZE");
		
		_startFrom = cg::Vector3d(-wordlSize, 0, - wordlSize);
	}
	
	Block::~Block() {}
	
	void Block::draw(int f, int bk, int l, int r, int t, int bt, int startLine, int endLine, int startColumn, int endColumn, int depth){
		
		_startPoint = cg::Vector3d(_startFrom[0] + _blockSize*startLine, 
					   _startFrom[1] + _blockSize*depth, 
					   _startFrom[2] + _blockSize*startColumn);
		
		_endPoint = cg::Vector3d(_startFrom[0] + _blockSize*(endLine+1), 
					 _startFrom[1] + _blockSize*depth + _blockSize, 
					 _startFrom[2] + _blockSize*(endColumn+1));
		
		int lines = endLine-startLine+1; //number of lines to be drawn
		int columns = endColumn-startColumn+1; // number of columns to be draw
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _materialDL);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		GLfloat mat_ambient[] = {1.0f,1.0f,1.0f,1.0f};
		GLfloat mat_difusse[] = {0.3f,0.9f,0.3f,1.0f};
		GLfloat mat_specular[] = {0.3f,0.3f,0.3f,1.0f};
		
		glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difusse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, 12);
		
		glBegin(GL_QUADS);
		{
			if (f) { drawFrontFace(lines, columns); }
			if (bk) { drawBackFace(lines, columns); }
			if (l) { drawLeftFace(lines, columns); }
			if (r) { drawRightFace(lines, columns); }
			if (t) { drawTopFace(lines, columns); }
			if (bt) { drawBottomFace(lines, columns); }
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);

	}
	
	void Block::drawTopFace(int lines, int columns) 
	{
		glTexCoord2d(0, columns);
		glVertex3d(_startPoint[0], _endPoint[1], _startPoint[2]);
		glTexCoord2d(lines, columns);
		glVertex3d(_endPoint[0], _endPoint[1], _startPoint[2]);
		glTexCoord2d(lines, 0);
		glVertex3d(_endPoint[0], _endPoint[1], _endPoint[2]);
		glTexCoord2d(0, 0);
		glVertex3d(_startPoint[0], _endPoint[1], _endPoint[2]);
	}
	
	void Block::drawRightFace(int lines, int columns)
	{
		glTexCoord2d(0, 1);
		glVertex3d(_endPoint[0], _endPoint[1], _startPoint[2]);
		glTexCoord2d(columns, 1);
		glVertex3d(_endPoint[0], _endPoint[1], _endPoint[2]);
		glTexCoord2d(columns, 0);
		glVertex3d(_endPoint[0], _startPoint[1], _endPoint[2]);
		glTexCoord2d(0, 0);
		glVertex3d(_endPoint[0], _startPoint[1], _startPoint[2]);
	}
	
	void Block::drawLeftFace(int lines, int columns)
	{
		glTexCoord2d(1, columns);
		glVertex3d(_startPoint[0], _endPoint[1], _startPoint[2]);
		glTexCoord2d(0, columns);
		glVertex3d(_startPoint[0], _endPoint[1], _endPoint[2]);
		glTexCoord2d(0, 0);
		glVertex3d(_startPoint[0], _startPoint[1], _endPoint[2]);
		glTexCoord2d(1, 0);
		glVertex3d(_startPoint[0], _startPoint[1], _startPoint[2]);
	}
	
	void Block::drawFrontFace(int lines, int columns)
	{
		glTexCoord2d(0, 1);
		glVertex3d(_startPoint[0], _endPoint[1], _endPoint[2]);
		glTexCoord2d(0, 0);
		glVertex3d(_startPoint[0], _startPoint[1], _endPoint[2]);
		glTexCoord2d(lines, 0);
		glVertex3d(_endPoint[0], _startPoint[1], _endPoint[2]);
		glTexCoord2d(lines, 1);
		glVertex3d(_endPoint[0], _endPoint[1], _endPoint[2]);
	}
	
	void Block::drawBottomFace(int lines, int columns)
	{
		glTexCoord2d(0, columns);
		glVertex3d(_startPoint[0], _startPoint[1] - _blockSize, _startPoint[2]);
		glTexCoord2d(0, 0);
		glVertex3d(_startPoint[0], _startPoint[1] - _blockSize, _startPoint[2] - _blockSize);
		glTexCoord2d(lines, 0);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1] - _blockSize, _startPoint[2] - _blockSize);
		glTexCoord2d(lines, columns);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1] - _blockSize, _startPoint[2]);
	}
	
	void Block::drawBackFace(int lines, int columns)
	{
		glTexCoord2d(lines, columns);
		glVertex3d(_startPoint[0], _startPoint[1], _startPoint[2] - _blockSize);
		glTexCoord2d(0, columns);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1], _startPoint[2] - _blockSize);
		glTexCoord2d(0, 0);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1] - _blockSize, _startPoint[2] - _blockSize);
		glTexCoord2d(lines, 0);
		glVertex3d(_startPoint[0], _startPoint[1] - _blockSize, _startPoint[2] - _blockSize);
	}
	
	int Block::getTexture()
	{
		return _materialDL;
	}
}