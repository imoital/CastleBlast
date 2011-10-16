//
//  SceneManager.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SceneManager.h"

namespace CastleBlast {
	
	std::vector<std::vector<int> > SceneManager::createMatrix() {
		
		std::vector<std::vector<int> > matrix(_worldSize, std::vector<int>(_worldSize, 1));
		
		return matrix;
	}
	
	SceneManager::SceneManager() : cg::Entity("SCENE_MANAGER") {}
	
	SceneManager::~SceneManager() {}
	
	void SceneManager::init()
	{
		_worldSize = cg::Properties::instance()->getInt("WORLD_SIZE");
		_block = new GrassBlock();
		_world = createMatrix();
		_projectile = new Projectile();
	}
	
	void SceneManager::draw()
	{
		
		glPushMatrix();
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _block->getTexture());
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		glBegin(GL_QUADS);
		
		for (int i = 0; i < _worldSize; i++) {
			for (int j = 0; j < _worldSize; j++) {
				if (_world[i][j]) {
					
					int df = 1;
					int dbk = 1;
					int dl = 1;
					int dr = 1;
					int dt = 1;
					int dbt = 1;
					
				/************************************************************
				 * Don't draw faces that aren't needed                      *
				 * TODO: needs to be in three dimensions                    *
				 ************************************************************/
					if (i != 0 && !_world[i-1][j]) df = 0;
					if (j != 0 && !_world[i][j-1]) dr = 0;
					if (i != _worldSize-1 && !_world[i+1][j]) dbk = 0;
					if (j != _worldSize-1 && !_world[i][j+1]) dl = 0;
				/************************************************************/
					_block->draw(df, dbk, dl, dr, dt, dbt, cg::Vector3d(i,j,0));
				}
			}
		}
		
		
		
		glEnd();
		_projectile->draw();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}