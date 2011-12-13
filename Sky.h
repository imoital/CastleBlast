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
	class Sky : public cg::Entity, public cg::IDrawListener, public cg::IUpdateListener, public cg::IMouseEventListener{
	public:
		Sky();
		~Sky();
		double _red;
		double _green;
		double _blue;
		void init();
		void draw();
		void update(unsigned long elapsed_millis);
		void setLevel(int level);
		
	private:
		int _worldSize;
		void setLevel1();
		void setLevel2();
	};
}

#endif