//
//  ModelManager.cpp
//  Project
//
//  Created by Inês on 11/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ModelManager.h"
#include "Model.h"

namespace CastleBlast {
	
	ModelManager::ModelManager() : cg::Entity("MODEL_MANAGER") {}
	
	ModelManager::~ModelManager() {}
	
	void ModelManager::init() {}
	
	void ModelManager::newModel(std::string type, const char* filename) {
		
		std::map<std::string, Model*>::iterator model = _models.find(type);
		
		if (model == _models.end()) {
			Model* newModel = new Model();
			newModel->loadModelData(filename);
			
			_models.insert(std::pair<std::string, Model*>(type, newModel));
		}
		
	}
	
	void ModelManager::drawModel(std::string type) {
		std::map<std::string, Model*>::iterator model = _models.find(type);
		
		model->second->drawModel();
	}
}