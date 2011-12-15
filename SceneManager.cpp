//
//  SceneManager.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SceneManager.h"
#include "Loader.h"

namespace CastleBlast {
	
	std::vector<std::vector<std::vector<int> > > SceneManager::createWorld()
	{
		
		std::vector<std::vector<int> > tmp(_worldSize, std::vector<int>(_worldSize, 0));
		std::vector<std::vector<std::vector<int> > > matrix(_worldHeight, tmp);
		
		//Loads the terrain
#ifdef __APPLE__
		std::vector<std::vector<int> > terrain = Loader::createHeightMap("HeightMaps/terrain.png", 6);
#else
		std::vector<std::vector<int> > terrain = Loader::createHeightMap("..\\..\\src\\HeightMaps\\terrain.png", 6);
#endif
		
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < _worldSize; j++) {
				for (int k = 0; k < _worldSize; k++) {
					if (terrain[j][k] > 0){
						matrix[i][j][k] = 1;
						terrain[j][k]--;
					}
				}
			}
		}
		
		return matrix;
	}
	
	void SceneManager::initWorldMatrix()
	{
		cast = true;
		_world = _worldOriginal;
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
		updateQuads();
	}
	
	SceneManager::quads* SceneManager::makeQuad(int startLine, int startColumn, int endLine, int endColumn, int depth)
	{
		quads *q = (quads*)malloc(sizeof(quads));
		q->startLine = startLine;
		q->startColumn = startColumn;
		q->endLine = endLine;
		q->endColumn = endColumn;
		q->startDepth = depth;
		q->endDepth = depth;
		
		return q;
	}
	
	void SceneManager::initQuads() 
	{
		_quads.clear();
		for (int i = 0; i < 4; i++){
			std::vector<quads*> vec;
			_quads.push_back(vec);
		}
	}
	
	SceneManager::SceneManager() : cg::Entity("SCENE_MANAGER"), Collidable(0,0,0)
	{
		_worldSize = cg::Properties::instance()->getInt("WORLD_SIZE");
		_worldHeight = cg::Properties::instance()->getInt("WORLD_HEIGHT");
		_blockSize = cg::Properties::instance()->getInt("BLOCK_SIZE");
		_startFrom  = cg::Vector3d(-_worldSize, 0, -_worldSize);
		_grassBlock = new GrassBlock(_startFrom);
		_stoneBlock = new StoneBlock(_startFrom);
		_stone2Block = new Stone2Block(_startFrom);
		loadCastleHeightMap();
		_worldOriginal = createWorld();
		//_world = createWorld();
		initWorldMatrix();
		updateQuads();
	}
	
	SceneManager::~SceneManager() {}
	
	void SceneManager::updateQuads()
	{
		initQuads();
		
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
					    q1->startDepth == q2->startDepth) {
						q1->endLine = q2->endLine;
						_quads[type].erase(_quads[type].begin()+j);
						j--;
					}
				}
			}
		}
		
		// TODO: depth in blocks
		for (int type = 0; type < _quads.size(); type++) {
			for (int i = 0; i < _quads[type].size(); i++) {
				for (int j = i+1; j < _quads[type].size(); j++) {
					quads *q1 = _quads[type][i];
					quads *q2 = _quads[type][j];
					
					if (q1->startColumn == q2->startColumn && 
					    q1->endColumn == q2->endColumn && 
					    q1->endLine == q2->endLine &&
					    q1->startLine == q2->startLine &&
					    q1->endDepth == q2->startDepth-1) {
						q1->endDepth = q2->startDepth;
						_quads[type].erase(_quads[type].begin()+j);
						j--;
					}
				}
			}
		}
		
		int nQuads = 0;
		for (int m = 0; m < _quads.size(); m++) {
			nQuads = nQuads + _quads[m].size();
		}
	}
	
	void SceneManager::init()
	{}
	
	void SceneManager::draw()
	{
		
		glPushMatrix();
		{
			for (int i = 0; i < _quads.size(); i++) {
				for (int j = 0; j < _quads[i].size(); j++){
					
					if (i == 0){
						_grassBlock->draw(_quads[i][j]->startLine, 
								  _quads[i][j]->endLine, 
								  _quads[i][j]->startColumn, 
								  _quads[i][j]->endColumn, 
								  _quads[i][j]->startDepth,
								  _quads[i][j]->endDepth);
					}
					else if (i == 1){
						_stoneBlock->draw(_quads[i][j]->startLine, 
								  _quads[i][j]->endLine, 
								  _quads[i][j]->startColumn, 
								  _quads[i][j]->endColumn, 
								  _quads[i][j]->startDepth,
								  _quads[i][j]->endDepth);
					} else if (i == 2){
						_stone2Block->draw(_quads[i][j]->startLine, 
								  _quads[i][j]->endLine, 
								  _quads[i][j]->startColumn, 
								  _quads[i][j]->endColumn, 
								  _quads[i][j]->startDepth,
								  _quads[i][j]->endDepth);
					}
				}
			}
		}
		glPopMatrix();
	}
	
	cg::Vector3d SceneManager::getWorldPosition(int posX, int posY)
	{
		int i;
		
		for (i = 0; i < _worldHeight; i++)
		{
			if (_worldOriginal[i][posX][posY] == 0)
				break;
		}
		
		float x = _startFrom[0] + _blockSize*(posX+1);
		float y = _startFrom[1] + i*_blockSize;
		float z = _startFrom[2] + _blockSize*posY;
		
		return cg::Vector3d(x, y, z);
	}
	
	void SceneManager::update(unsigned long elapsed_millis) {}
	
	void SceneManager::placeCastle(int posX, int posY)
	{
		std::vector<std::vector<int> > castle = _castle;
		
		int minz = _worldHeight;
		
		for (int i = posX; i < posX+30; i++){
			for (int j = posY; j < posY+30; j++){
				for (int k = 0; k < _worldHeight; k++) {
					if (_worldOriginal[k][i][j] == 0 && minz > k){
						minz = k;
						break;
					}
				}
			}
		}
		
		for (int i = minz; i < _worldHeight; i++) {
			for (int j = posX, a = 0; a < 30; a++, j++){
				for (int k = posY, b = 0; b < 30; b++, k++) {
					if (castle[a][b] > 0) {
						if(cast){
							_worldOriginal[i][j][k] = 2;
							_world[i][j][k] = 2;
							castle[a][b]--;
						} else {
							_worldOriginal[i][j][k] = 3;
							_world[i][j][k] = 3;
							castle[a][b]--;
						}
					}
				}
			}
		}

		if(cast) 
			cast = false;
		else 
			cast = true;
		
		updateQuads();
	}
	
	void SceneManager::loadCastleHeightMap()
	{
		// Loads the castle
		// 13 is the height of the castle
#ifdef __APPLE__
		_castle = Loader::createHeightMap("HeightMaps/castle.png", 13);
#else
		_castle = Loader::createHeightMap("..\\..\\src\\HeightMaps\\castle.png", 13);
#endif
	}
	
	int SceneManager::getWorldSize()
	{
		return _worldSize;
	}
	
	int SceneManager::getXMatrixPos(double x) 
	{
		return (x-_startFrom[0])/_blockSize;
	}
	
	int SceneManager::getYMatrixPos(double y)
	{
		return (y-_startFrom[1])/_blockSize;
	}
	
	int SceneManager::getZMatrixPos(double z)
	{
		return (z-_startFrom[2])/_blockSize;
	}
	
	bool SceneManager::isCollision(CastleBlast::Collidable *obj)
	{
		boundaries otherObjectBoundaries = obj->getBoundaries();
		
		int i_max = getXMatrixPos(otherObjectBoundaries.x_min);
		int i_min = getXMatrixPos(otherObjectBoundaries.x_max);
		int k_max = getYMatrixPos(otherObjectBoundaries.y_min);
		int k_min = getYMatrixPos(otherObjectBoundaries.y_max);
		int j_max = getZMatrixPos(otherObjectBoundaries.z_min);
		int j_min = getZMatrixPos(otherObjectBoundaries.z_max);
		
		if (i_max <= 0 || i_min <= 0 || j_min <= 0 || j_max <= 0 || k_min <= 0 || k_max <= 0)
			return true;
		
		if (i_max >= _worldSize || i_min >= _worldSize || j_min >= _worldSize || j_max >= _worldSize || k_min >= _worldHeight || k_max >= _worldHeight)
			return false;
		
		bool collided = false;
		std::vector<cg::Vector3d> positions;
		
		if (_worldOriginal[k_min][i_min][j_min] != 0) {
			positions.push_back(cg::Vector3d(i_min, j_min, k_min));
			collided = true;
		}
		if(_worldOriginal[k_min][i_max][j_min] != 0) {
			positions.push_back(cg::Vector3d(i_max, j_min, k_min));
			collided = true;
		}
		if(_worldOriginal[k_max][i_max][j_min] != 0) {
			positions.push_back(cg::Vector3d(i_max, j_min, k_max));
			collided = true;
		}
		if(_worldOriginal[k_max][i_min][j_min] != 0) {
			positions.push_back(cg::Vector3d(i_min, j_min, k_max));
			collided = true;
		}
		if(_worldOriginal[k_max][i_min][j_max] != 0) {
			positions.push_back(cg::Vector3d(i_min, j_max, k_max));
			collided = true;
		}
		if(_worldOriginal[k_max][i_max][j_max] != 0) {
			positions.push_back(cg::Vector3d(i_max, j_max, k_max));
			collided = true;
		}
		if(_worldOriginal[k_min][i_max][j_max] != 0) {
			positions.push_back(cg::Vector3d(i_max, j_max, k_min));
			collided = true;
		}
		if(_worldOriginal[k_min][i_min][j_max] != 0) {
			positions.push_back(cg::Vector3d(i_min, j_max, k_min));
			collided = true;
		}
		
		if (collided)
			collision(positions);
					    
		return collided;
	}
	
	void SceneManager::collision(std::vector<cg::Vector3d> positions) 
	{
		int posX, posY, posZ;
		
		for (int i = 0; i < positions.size(); i++) {
			destroyCircle(positions[i], 2);
		}
		initWorldMatrix();
	}
	
	void SceneManager::destroyCircle(cg::Vector3d center, int radios) {
	
		bool removeCenter = true;
		
		if(center[0] > 1 && center[0] < _worldSize){
			_worldOriginal[center[2]][center[0]-1][center[1]] = 0;
			_worldOriginal[center[2]][center[0]+1][center[1]] = 0;
			if (radios>1) {
				destroyCircle(cg::Vector3d(center[0]-1,center[1],center[2]), radios-1);
				destroyCircle(cg::Vector3d(center[0]+1,center[1],center[2]), radios-1);
			}
		} else removeCenter = false;
		if(center[1] > 1 && center[1] < _worldSize){
			_worldOriginal[center[2]][center[0]][center[1]-1] = 0;
			_worldOriginal[center[2]][center[0]][center[1]+1] = 0;
			if (radios>1) {
				destroyCircle(cg::Vector3d(center[0],center[1]-1,center[2]), radios-1);
				destroyCircle(cg::Vector3d(center[0],center[1]+1,center[2]), radios-1);
			}
		} else removeCenter = false;
		if (center[2] > 1 && center[2] < _worldHeight) {
			_worldOriginal[center[2]-1][center[0]][center[1]] = 0;
			_worldOriginal[center[2]+1][center[0]][center[1]] = 0;
			if (radios > 1){				
				destroyCircle(cg::Vector3d(center[0],center[1],center[2]-1), radios-1);
				destroyCircle(cg::Vector3d(center[0],center[1],center[2]+1), radios-1);
			}
		} else removeCenter = false;
		
		if (removeCenter)
			_worldOriginal[center[2]][center[0]][center[1]] = 0;
	}
	
	void SceneManager::restart()
	{
		_worldOriginal = createWorld();
		//_world = createWorld();
		initWorldMatrix();
		updateQuads();
	}
}