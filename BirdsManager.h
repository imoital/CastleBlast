//
//  BirdsManager.h
//  CastleBlast
//
//  Created by Inês on 12/6/11.
//  Copyright 2011 AVT. All rights reserved.
//

#ifndef BIRDS_MANAGER_H
#define BIRDS_MANAGER_H

#include <cg/cg.h>

namespace CastleBlast {
	class Birds;
	
	class BirdsManager : public cg::Group, public cg::GroupDraw, public cg::GroupUpdate, public cg::IMouseEventListener {
	public:
		
		BirdsManager();
		~BirdsManager();
		
		void createEntities();
	};
}

#endif