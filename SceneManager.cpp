//
//  SceneManager.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SceneManager.h"

namespace CastleBlast {
	
	std::vector<std::vector<std::vector<int> > > SceneManager::createMatrix()
	{
		
		std::vector<std::vector<int> > tmp(_worldSize, std::vector<int>(_worldSize, 0));
		std::vector<std::vector<std::vector<int> > > matrix(_worldHeight, tmp);
		
		for (int i = 0; i < _worldSize; i++) {
			for (int j = 0; j < _worldSize; j++) {
				matrix[0][i][j] = 1;
			}
		}
		
		//CASTLE
		int c[19][20] = { 
			{13, 12, 13, 12, 13, 7, 8, 7, 8, 7, 8, 7, 8, 7, 13, 12, 13, 12, 13,0},
			{12, 11, 11, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 11, 11, 11, 12,0},
			{13, 11, 11, 11, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 11, 11, 11, 13,0},
			{12, 11, 11, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 11, 11, 11, 12,0},
			{13, 12, 13, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 13, 12, 13,0},
			{7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0},
			{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6},
			{7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, -6},
			{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, -6},
			{7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, -6},
			{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, -6},
			{7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, -6},
			{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6},
			{7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0},
			{13, 12, 13, 12, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 12, 13, 12, 13, 0},
			{12, 11, 11, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 11, 11, 11, 12, 0},
			{13, 11, 11, 11, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 11, 11, 11, 13, 0},
			{12, 11, 11, 11, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 11, 11, 11, 12, 0},
			{13, 12, 13, 12, 13, 7, 8, 7, 8, 7, 8, 7, 8, 7, 13, 12, 13, 12, 13, 0}};
		
		for (int i = 1; i < _worldHeight; i++) {
			for (int j = 160, a = 0; a < 19; a++, j++){
				for (int k = 150, b = 0; b < 20; b++, k++) {
					if (c[a][b] > 0) {
						matrix[i][j][k] = 3;
						c[a][b]--;
					}
					if (c[a][b] < 0) {
						c[a][b]++;
						if (c[a][b] == -1)
							c[a][b] = 1;
					}
				}
			}
		}
		
		return matrix;
	}
	
	void SceneManager::initWorldMatrix()
	{
		for (int i = 0; i < _worldHeight; i++) {
			for (int j = 0; j < _worldSize; j++) {
				for (int k = 0; k < _worldSize; k++) {
					if (i == 0 || j == 0 || k == 0 || 
					    i == _worldHeight-1 || j == _worldSize-1 || k == _worldSize-1)
						_world[i][j][k] = _worldOriginal[i][j][k];
					
					else if (_worldOriginal[i-1][j][k] != 0 && 
						 _worldOriginal[i+1][j][k] != 0 &&
						 _worldOriginal[i][j-1][k] != 0 && 
						 _worldOriginal[i][j+1][k] != 0 &&
						 _worldOriginal[i][j][k-1] != 0 &&
						 _worldOriginal[i][j][k+1] != 0)
						
						_world[i][j][k] = 0;
				}
			}
		}
	}
	
	SceneManager::quads* SceneManager::makeQuad(int startLine, int startColumn, int endLine, int endColumn, int depth)
	{
		quads *q = (quads*)malloc(sizeof(quads));
		q->startLine = startLine;
		q->startColumn = startColumn;
		q->endLine = endLine;
		q->endColumn = endColumn;
		q->depth = depth;
		
		return q;
	}
	
	void SceneManager::initQuads() 
	{
		for (int i = 0; i < 4; i++){
			std::vector<quads*> vec;
			_quads.push_back(vec);
		}
	}
	
	SceneManager::SceneManager() : cg::Entity("SCENE_MANAGER") {}
	
	SceneManager::~SceneManager() {}
	
	void SceneManager::updateQuads()
	{
		// clear all the contents in the _quads vector for each type
		for (int i = 0; i < 4; i++) {
			_quads[i].clear();
		}
		
		int prevType = -1;
		for (int i = 0; i < _worldHeight; i++) { // world level
			for (int j = 0; j < _worldSize; j++) {
				bool startNewQuad = true;
				for (int k = 0; k < _worldSize; k++) {
					
					int type = _world[i][j][k];
					if (type == 0 && prevType > 0 && _quads[prevType-1].back()->endColumn != k-1 && _quads[prevType-1].back()->endLine == j) {
						quads *newQ = makeQuad(j, _quads[prevType-1].back()->startColumn, j, k-1, i);
						_quads[prevType-1].push_back(newQ);
					}
					if (type != 0) {
						if (_quads[type-1].size() == 0) {
							quads *q = makeQuad(j, k, j, k, i);
							_quads[type-1].push_back(q);
							if (prevType > 0) {
								if (startNewQuad) {
									quads *prevQ = _quads[prevType-1].back();
									quads *newQ = makeQuad(prevQ->endLine, prevQ->startColumn, prevQ->endLine, k-1, i);
									_quads[prevType-1].push_back(newQ);
									if (prevQ->startLine != prevQ->endLine)
										prevQ->endLine = prevQ->endLine-1;
									startNewQuad = false;
								}
							}
						}
						else {
							if (prevType == 0) {
								quads *newQ = makeQuad(j, k, j, k, i);
								_quads[type-1].push_back(newQ);
							}
							else {
								if (prevType == type) {
									quads *q = _quads[type-1].back();
									if (q->startColumn > k){
										quads *newQ = makeQuad(j, k, j, k, i);
										_quads[type-1].push_back(newQ);
									}
									else {
										q->endLine = j;
										if (q->endColumn < k)
											q->endColumn = k;
									}
								}
								else {
									quads *prevQ = _quads[prevType-1].back();
									if (prevQ->endLine != prevQ->startLine && startNewQuad){
										quads *newQ = makeQuad(prevQ->endLine, prevQ->startColumn, prevQ->endLine, k-1, i);
										_quads[prevType-1].push_back(newQ);
										prevQ->endLine = prevQ->endLine-1;
										startNewQuad = false;
									}
									else {
										quads *newQ = makeQuad(j, k, j, k, i);
										_quads[type-1].push_back(newQ);
									}
								}
							}
						}
					}
					prevType = type;
				}
			}
		}
		
		for (int type = 0; type < _quads.size(); type++) {
			for (int i = 0; i < _quads[type].size(); i++) {
				for (int j = i+1; j < _quads[type].size(); j++) {
					quads *q1 = _quads[type][i];
					quads *q2 = _quads[type][j];
					
					if (q1->startColumn == q2->startColumn && 
					    q1->endColumn == q2->endColumn && 
					    q1->endLine == q2->startLine-1 &&
					    q1->depth == q2->depth) {
						q1->endLine = q2->endLine;
						_quads[type].erase(_quads[type].begin()+j);
						j--;
					}
				}
			}
		}
		
		for (int m = 0; m < _quads.size(); m++) {
			std::cout << "quad type : " << m+1 << std::endl;
			for (int n = 0; n < _quads[m].size(); n++){
				std::cout << "    Quad " << n << std::endl;
				std::cout << "        StartLine: " << _quads[m][n]->startLine << "  EndLine: " << _quads[m][n]->endLine << std::endl;
				std::cout << "        StartColumn: " << _quads[m][n]->startColumn << "  EndColumn: " << _quads[m][n]->endColumn << std::endl;
				std::cout << "        Depth: " << _quads[m][n]->depth << std::endl;
			}
		}
	}
	
	void SceneManager::init()
	{
		_worldSize = cg::Properties::instance()->getInt("WORLD_SIZE");
		_worldHeight = cg::Properties::instance()->getInt("WORLD_HEIGHT");
		_grassBlock = new GrassBlock();
		_stoneBlock = new StoneBlock();
		_worldOriginal = createMatrix();
		_world = createMatrix();
		initWorldMatrix();
		_projectile = new Projectile();
		initQuads();
		
		
		updateQuads();
	}
	
	void SceneManager::draw()
	{
		
		glPushMatrix();
		
		
		for (int i = 0; i < _quads.size(); i++) {
			for (int j = 0; j < _quads[i].size(); j++){
				
				if (i == 0){
					_grassBlock->draw(1, 0, 1, 1, 1, 0, _quads[i][j]->startLine, _quads[i][j]->endLine, _quads[i][j]->startColumn, _quads[i][j]->endColumn, _quads[i][j]->depth);
				}
				if (i == 2){
					_stoneBlock->draw(1, 0, 1, 1, 1, 0, _quads[i][j]->startLine, _quads[i][j]->endLine, _quads[i][j]->startColumn, _quads[i][j]->endColumn, _quads[i][j]->depth);
				}
			}
		}
		
		_projectile->draw();
		glPopMatrix();
	}
}