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
	
	void Block::draw(int f, int bk, int l, int r, int t, int bt, cg::Vector3d matrixPos){
		
		_startPoint = cg::Vector3d(_startFrom[0] + _blockSize*matrixPos[1], 0, _startFrom[2] + _blockSize*matrixPos[0]);
		
		if (f) { drawFrontFace(); }
		if (bk) { drawBackFace(); }
		if (l) { drawLeftFace(); }
		if (r) { drawRightFace(); }
		if (t) { drawTopFace(); }
		if (bt) { drawBottomFace(); }

	}
	
	void Block::drawTopFace() 
	{
		glTexCoord2d(0, 1);
		glVertex3d(_startPoint[0], _startPoint[1], _startPoint[2] - _blockSize);
		glTexCoord2d(1, 1);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1], _startPoint[2] - _blockSize);
		glTexCoord2d(1, 0);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1], _startPoint[2]);
		glTexCoord2d(0, 0);
		glVertex3d(_startPoint[0], _startPoint[1], _startPoint[2]);
	}
	
	void Block::drawRightFace()
	{
		glTexCoord2d(0, 1);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1], _startPoint[2]);
		glTexCoord2d(1, 1);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1], _startPoint[2] - _blockSize);
		glTexCoord2d(1, 0);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1] - _blockSize, _startPoint[2] - _blockSize);
		glTexCoord2d(0, 0);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1] - _blockSize, _startPoint[2]);
	}
	
	void Block::drawLeftFace()
	{
		glTexCoord2d(1, 1);
		glVertex3d(_startPoint[0], _startPoint[1], _startPoint[2]);
		glTexCoord2d(0, 1);
		glVertex3d(_startPoint[0], _startPoint[1], _startPoint[2] - _blockSize);
		glTexCoord2d(0, 0);
		glVertex3d(_startPoint[0], _startPoint[1] - _blockSize, _startPoint[2] - _blockSize);
		glTexCoord2d(1, 0);
		glVertex3d(_startPoint[0], _startPoint[1] - _blockSize, _startPoint[2]);
	}
	
	void Block::drawFrontFace()
	{
		glTexCoord2d(0, 1);
		glVertex3d(_startPoint[0], _startPoint[1], _startPoint[2]);
		glTexCoord2d(0, 0);
		glVertex3d(_startPoint[0], _startPoint[1] - _blockSize, _startPoint[2]);
		glTexCoord2d(1, 0);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1] - _blockSize, _startPoint[2]);
		glTexCoord2d(1, 1);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1], _startPoint[2]);
	}
	
	void Block::drawBottomFace()
	{
		glTexCoord2d(0, 1);
		glVertex3d(_startPoint[0], _startPoint[1] - _blockSize, _startPoint[2]);
		glTexCoord2d(0, 0);
		glVertex3d(_startPoint[0], _startPoint[1] - _blockSize, _startPoint[2] - _blockSize);
		glTexCoord2d(1, 0);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1] - _blockSize, _startPoint[2] - _blockSize);
		glTexCoord2d(1, 1);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1] - _blockSize, _startPoint[2]);
	}
	
	void Block::drawBackFace()
	{
		glTexCoord2d(1, 1);
		glVertex3d(_startPoint[0], _startPoint[1], _startPoint[2] - _blockSize);
		glTexCoord2d(0, 1);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1], _startPoint[2] - _blockSize);
		glTexCoord2d(0, 0);
		glVertex3d(_startPoint[0] + _blockSize, _startPoint[1] - _blockSize, _startPoint[2] - _blockSize);
		glTexCoord2d(1, 0);
		glVertex3d(_startPoint[0], _startPoint[1] - _blockSize, _startPoint[2] - _blockSize);
	}
	
	int Block::getTexture()
	{
		return _materialDL;
	}
}