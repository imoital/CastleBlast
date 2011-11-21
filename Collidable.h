//
//  Collidable.h
//  Project
//
//  Created by Inês on 11/15/11.
//  Copyright 2011 AVT. All rights reserved.
//

namespace CastleBlast {
	
	class Collidable {
		
	public:
		virtual bool isCollision(Collidable* otherObj) = 0;
		void notify();
	};
}