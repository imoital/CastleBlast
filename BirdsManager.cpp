//
//  BirdsManager.cpp
//  CastleBlast
//
//  Created by Inês on 12/6/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include "BirdsManager.h"
#include "Bird.h"

namespace CastleBlast {
	
	BirdsManager::BirdsManager() : cg::Group("BIRDS_MANAGER") {}
	
	BirdsManager::~BirdsManager() {}
	
	void BirdsManager::createEntities()
	{
		int numBirds = cg::Properties::instance()->getInt("NUM_BIRDS");
		
		for (int i = 0; i < numBirds; i++) {
			std::stringstream birdName;
			birdName << "BIRD" << i;
			addAtBeginning(new Bird(birdName.str(), rand()%360));
		}
	}
}