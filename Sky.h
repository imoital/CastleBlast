//
//  Sky.h
//  Project
//
//  Created by Inês on 10/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef SKY_H
#define SKY_H

#include "cg/cg.h"

namespace CastleBlast {
	
	//Sky : a sheper that represents the sky
	class Sky : public cg::Entity, public cg::IDrawListener{
	public:
		Sky();
		~Sky();
		
		void init();
		void draw();
		
	private:
		int _worldSize;
	};
}

#endif