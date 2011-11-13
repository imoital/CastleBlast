//
//  GameManager.h
//  Project
//
//  Created by Inês on 11/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "cg/cg.h"

namespace CastleBlast {
	
	class SceneManager;
	class Player;
	
	class GameManager : public cg::Group, public cg::GroupDraw, public cg::GroupUpdate {
	private:
		SceneManager* _sceneManager;
		Player* _player1;
	public:
		GameManager();
		~GameManager();
		
		void preInit();
		void postInit();
		void createEntities();
	};
}