//
//  App.h
//  Project
//
//  Created by Inês on 10/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <cg/cg.h>

namespace AVT {
	class App : public cg::Application {
	public:
		App();
		~App();
		void createEntities();
		void createViews();
	};
}