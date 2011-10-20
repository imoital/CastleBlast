//
//  Lights.cpp
//  Project
//
//  Created by Inês on 10/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Lights.h"

namespace CastleBlast {
	
	Lights::Lights() :cg::Entity("LIGHTS"){}
	
	Lights::~Lights() {}
	
	void Lights::init() 
	{
		GLfloat ambient_light[] = {1.0f,1.0f,1.0f,1.0f};
		GLfloat diffuse_light[] = {1.0f,1.0f,1.0f,1.0f};
		GLfloat specular_light[] = {0.9f,0.9f,0.9f,1.0f};
		GLfloat position_light[] = {5.0f, 30.0f, 10.0f};
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
		glLightfv(GL_LIGHT0, GL_POSITION, position_light);
		//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);
	}
}