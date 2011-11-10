//
//  Fog.cpp
//  Project
//
//  Created by Inês on 10/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Fog.h"

namespace CastleBlast {
	
	Fog::Fog() : cg::Entity("FOG") {}
	
	Fog::~Fog() {}
	
	void Fog::init()
	{
		_density = 1;

		_fogColor[0] = 0.53;
		_fogColor[1] = 0.81;
		_fogColor[2] = 0.98;
		_fogColor[3] = 1.0;
	}
	
	void Fog::draw()
	{
		glEnable (GL_DEPTH_TEST);
		glEnable (GL_FOG); //enable the fog
		glFogi (GL_FOG_MODE, GL_LINEAR);
		glFogfv (GL_FOG_COLOR, _fogColor); 
		glFogf (GL_FOG_DENSITY, _density); 
		glFogf(GL_FOG_START, 300.f);
		glFogf(GL_FOG_END, 500.f);
		glHint (GL_FOG_HINT, GL_NICEST);
		
	}
}
