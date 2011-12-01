//
//  Collidable.h
//  Project
//
//  Created by Inês on 11/15/11.
//  Copyright 2011 AVT. All rights reserved.
//

namespace CastleBlast {
	
	class CollisionManager;
	
	class Collidable {
	private:
		int _x_min, _x_max, _y_min, _y_max, _z_min, _z_max;
		CollisionManager* _collisionManager;
		
	public:
		Collidable(/*int x_min, int x_max, int y_min, int y_max, int z_min, int z_max*/);
		~Collidable();
		
		virtual bool isCollision(double x_min, double x_max, double y_min, double y_max, double z_min, double z_max) = 0;
		void notify();
	};
}