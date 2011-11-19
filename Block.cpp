//
//  Block.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Block.h"

namespace CastleBlast {
	
	Block::Block(cg::Vector3d startFrom) 
	{
		_blockSize = cg::Properties::instance()->getInt("BLOCK_SIZE");
		_startFrom = startFrom;
		
		//default material for block
		topBottom_mat_ambient[0] = 0.9f;
		topBottom_mat_ambient[1] = 0.9f;
		topBottom_mat_ambient[2] = 0.9f;
		topBottom_mat_ambient[3] = 1.0f;
		
		topBottom_mat_difusse[0] = 0.3f;
		topBottom_mat_difusse[1] = 0.9f;
		topBottom_mat_difusse[2] = 0.3f;
		topBottom_mat_difusse[3] = 1.0f;
		
		topBottom_mat_specular[0] = 0.3f;
		topBottom_mat_specular[1] = 0.3f;
		topBottom_mat_specular[2] = 0.3f;
		topBottom_mat_specular[3] = 1.0f;
		
		topBottom_shininess = 12;
		
		side_mat_ambient[0] = 0.9f;
		side_mat_ambient[1] = 0.9f;
		side_mat_ambient[2] = 0.9f;
		side_mat_ambient[3] = 1.0f;
		
		side_mat_difusse[0] = 0.3f;
		side_mat_difusse[1] = 0.9f;
		side_mat_difusse[2] = 0.3f;
		side_mat_difusse[3] = 1.0f;
		
		side_mat_specular[0] = 0.3f;
		side_mat_specular[1] = 0.3f;
		side_mat_specular[2] = 0.3f;
		side_mat_specular[3] = 1.0f;
		
		side_shininess = 12;
		
	}
	
	Block::~Block() {}
	
	void Block::draw(int startLine, int endLine, int startColumn, int endColumn, int depth){
		
		_startPoint = cg::Vector3d(_startFrom[0] + _blockSize*startLine, 
					   _startFrom[1] + _blockSize*depth, 
					   _startFrom[2] + _blockSize*startColumn);
		
		_endPoint = cg::Vector3d(_startFrom[0] + _blockSize*(endLine+1), 
					 _startFrom[1] + _blockSize*depth + _blockSize, 
					 _startFrom[2] + _blockSize*(endColumn+1));
		
		int lines = endLine-startLine+1; //number of lines to be drawn
		int columns = endColumn-startColumn+1; // number of columns to be draw
		
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

		//draw side faces
		glBindTexture(GL_TEXTURE_2D, _sideTexture);
		glMaterialfv(GL_FRONT,GL_AMBIENT, side_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, side_mat_difusse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, side_mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, side_shininess);
	
		drawFrontFace(lines, columns);
		drawBackFace(lines, columns);
		drawLeftFace(lines, columns);
		drawRightFace(lines, columns);
		
		// draw top and bottom faces
		glBindTexture(GL_TEXTURE_2D, _topBottomTexture);
		glMaterialfv(GL_FRONT,GL_AMBIENT, topBottom_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, topBottom_mat_difusse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, topBottom_mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, topBottom_shininess);
		
		drawTopFace(lines, columns);
		drawBottomFace(lines, columns);

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_CULL_FACE);

	}
	
	void Block::drawTopFace(int lines, int columns) 
	{
		glBegin(GL_QUADS);
		{
			glNormal3d(0, 1, 0);
			glTexCoord2d(0, columns);
			glVertex3d(_startPoint[0], _endPoint[1], _startPoint[2]);
			
			glNormal3d(0, 1, 0);
			glTexCoord2d(0, 0);
			glVertex3d(_startPoint[0], _endPoint[1], _endPoint[2]);
			
			glNormal3d(0, 1, 0);
			glTexCoord2d(lines, 0);
			glVertex3d(_endPoint[0], _endPoint[1], _endPoint[2]);
			
			glNormal3d(0, 1, 0);
			glTexCoord2d(lines, columns);
			glVertex3d(_endPoint[0], _endPoint[1], _startPoint[2]);
		}
		glEnd();
	}
	
	void Block::drawRightFace(int lines, int columns)
	{
		glBegin(GL_QUADS);
		{
			glNormal3d(-1, 0, 0);
			glTexCoord2d(0, 1);
			glVertex3d(_endPoint[0], _endPoint[1], _startPoint[2]);
			
			glNormal3d(-1, 0, 0);
			glTexCoord2d(columns, 1);
			glVertex3d(_endPoint[0], _endPoint[1], _endPoint[2]);
			
			glNormal3d(-1, 0, 0);
			glTexCoord2d(columns, 0);
			glVertex3d(_endPoint[0], _startPoint[1], _endPoint[2]);
			
			glNormal3d(-1, 0, 0);
			glTexCoord2d(0, 0);
			glVertex3d(_endPoint[0], _startPoint[1], _startPoint[2]);
		}
		glEnd();
	}
	
	void Block::drawLeftFace(int lines, int columns)
	{
		glBegin(GL_QUADS);
		{
			glNormal3d(1, 0, 0);
			glTexCoord2d(columns, 1);
			glVertex3d(_startPoint[0], _endPoint[1], _startPoint[2]);
			
			glNormal3d(1, 0, 0);
			glTexCoord2d(columns, 0);
			glVertex3d(_startPoint[0], _startPoint[1], _startPoint[2]);
			
			glNormal3d(1, 0, 0);
			glTexCoord2d(0, 0);
			glVertex3d(_startPoint[0], _startPoint[1], _endPoint[2]);
			
			glNormal3d(1, 0, 0);
			glTexCoord2d(0, 1);
			glVertex3d(_startPoint[0], _endPoint[1], _endPoint[2]);
		}
		glEnd();
	}
	
	void Block::drawFrontFace(int lines, int columns)
	{
		glBegin(GL_QUADS);
		{
			glNormal3d(0, 0, 1);
			glTexCoord2d(0, 1);
			glVertex3d(_startPoint[0], _endPoint[1], _endPoint[2]);
			
			glNormal3d(0, 0, 1);
			glTexCoord2d(0, 0);
			glVertex3d(_startPoint[0], _startPoint[1], _endPoint[2]);
			
			glNormal3d(0, 0, 1);
			glTexCoord2d(lines, 0);
			glVertex3d(_endPoint[0], _startPoint[1], _endPoint[2]);
			
			glNormal3d(0, 0, 1);
			glTexCoord2d(lines, 1);
			glVertex3d(_endPoint[0], _endPoint[1], _endPoint[2]);
		}
		glEnd();
	}
	
	void Block::drawBottomFace(int lines, int columns)
	{
		glBegin(GL_QUADS);
		{
			glNormal3d(0, -1, 0);
			glTexCoord2d(lines, columns);
			glVertex3d(_startPoint[0], _startPoint[1], _startPoint[2]);
			
			glNormal3d(0, -1, 0);
			glTexCoord2d(0, columns);
			glVertex3d(_endPoint[0], _startPoint[1], _startPoint[2]);
			
			glNormal3d(0, -1, 0);
			glTexCoord2d(0, 0);
			glVertex3d(_endPoint[0], _startPoint[1], _endPoint[2]);
			
			glNormal3d(0, -1, 0);
			glTexCoord2d(lines, 0);
			glVertex3d(_startPoint[0], _startPoint[1], _endPoint[2]);
			
		}
		glEnd();
	}
	
	void Block::drawBackFace(int lines, int columns)
	{
		glBegin(GL_QUADS);
		{
			glNormal3d(0, 0, -1);
			glTexCoord2d(lines, 1);
			glVertex3d(_startPoint[0], _endPoint[1], _startPoint[2]);
			
			glNormal3d(0, 0, -1);
			glTexCoord2d(0, 1);
			glVertex3d(_endPoint[0], _endPoint[1], _startPoint[2]);
			
			glNormal3d(0, 0, -1);
			glTexCoord2d(0, 0);
			glVertex3d(_endPoint[0], _startPoint[1], _startPoint[2]);
			
			glNormal3d(0, 0, -1);
			glTexCoord2d(lines, 0);
			glVertex3d(_startPoint[0], _startPoint[1], _startPoint[2]);
		}
		glEnd();
	}
}