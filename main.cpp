//
//  main.cpp
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "cg/cg.h"
#include "App.h"

int main(int argc, char** argv) {
	cg::Manager::instance()->runApp(new CastleBlast::App(),60,argc,argv);
	return 0;
}
