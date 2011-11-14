//
//  ModelManager.h
//  Project
//
//  Created by Inês on 11/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "cg/cg.h"
#include <map>

namespace CastleBlast {
	
	class Model;
	
	class ModelManager : public cg::Entity {
	private:
		std::map<std::string, Model*> _models;
		
	public:
		ModelManager();
		~ModelManager();
		
		void init();
		void newModel(std::string type, const char* filename);
		void drawModel(std::string type);
	};
}