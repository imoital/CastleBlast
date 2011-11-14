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
#include "StoneBlock.h"
#include "Projectile.h"
#include "FreeImage.h"

namespace CastleBlast {
	
	// SceneManager: this class will construct the scene
	//TODO: add more types of blocks to the scene
	class SceneManager : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener
	{
	public:
		SceneManager();
		~SceneManager();
		
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		cg::Vector3d getWorldPosition (int posX, int posY);
		void placeCastle (int posX, int posY);
		int getWorldSize();
		
	private:
		
		struct quads {
			int startLine;
			int endLine;
			int startColumn;
			int endColumn;
			int startDepth;
			int endDepth;
		};
		
		std::vector<std::vector<quads*> > _quads; // quads to be drawn for each type of block
		quads* makeQuad (int startLine, int startColumn, int endLine, int endColumn, int depth);
		void initQuads();
		void initWorldMatrix();
		
		int _worldSize; //the size of the world
		int _worldHeight;
		int _blockSize;
		cg::Vector3d _startFrom;
		Block *_grassBlock;
		Block *_stoneBlock;
		std::vector<std::vector<std::vector<int> > > _world;
		std::vector<std::vector<std::vector<int> > > _worldOriginal;	//matriz that represents the blocks in the world
		
		void updateQuads(); //turns the world matrix into quads
		
		//function that will create a matriz that represents the blocks in the world
		//TODO: need to represent more types of blocks
		std::vector<std::vector<std::vector<int> > > createWorld();
		
		void loadCastleHeightMap();
		std::vector<std::vector<int> > _castle;
		
	};
}

#endif