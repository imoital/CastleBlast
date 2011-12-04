//
//  App.h
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef APP_H
#define APP_H
#include <cg/cg.h>

namespace CastleBlast {
	class App : public cg::Application {
	public:
		App();
		~App();
		void createEntities();
		void createViews();
	};
}
#endif