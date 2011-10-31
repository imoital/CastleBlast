//
//  SceneManager.h
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SCENE_MANAGER
#define SCENE_MANAGER

#include <cg/cg.h>
#include "Block.h"
#include "GrassBlock.h"
#include "Projectile.h"

namespace CastleBlast {
	
	// SceneManager: this class will construct the scene
	//TODO: add more types of blocks to the scene
	class SceneManager : public cg::Entity, public cg::IDrawListener
	{
	public:
		SceneManager();
		~SceneManager();
		
		void init();
		void draw();
		
	private:
		
		struct quads {
			int startLine;
			int endLine;
			int startColumn;
			int endColumn;
			int depth;
		};
		
		std::vector<std::vector<quads*> > _quads; // quads to be drawn for each type of block
		quads* makeQuad (int startLine, int startColumn, int endLine, int endColumn, int depth);
		void initQuads();
		void initWorldMatrix();
		
		int _worldSize; //the size of the world
		int _worldHeight;
		Block *_block; //TODO: have more blocks of diferent types
		Projectile *_projectile;
		std::vector<std::vector<std::vector<int> > > _world;
		std::vector<std::vector<std::vector<int> > > _worldOriginal;	//matriz that represents the blocks in the world
		void updateQuads(); //turns the world matrix into quads
		
		//function that will create a matriz that represents the block in the world
		//TODO: need to be in three dimensions
		//TODO: need to represent more types of blocks
		std::vector<std::vector<std::vector<int> > > createMatrix();
		
	};
}

#endif