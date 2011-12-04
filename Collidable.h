//
//  Collidable.h
//  Project
//
//  Created by Inês on 11/15/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include <cg/cg.h>

#ifndef COLLIDABLE_H
#define COLLIDABLE_H

namespace CastleBlast {
	
	class CollisionManager;
	
	class Collidable {
		
	protected:	
		struct boundaries {
			double Xdimension;
			double Ydimension;
			double Zdimension;
			double x_min;
			double x_max;
			double y_min;
			double y_max;
			double z_min;
			double z_max;
		};
		
		boundaries _boundes;
		
	private:
		cg::Vector3d _objPosition;
		CollisionManager* _collisionManager;
		
		void setBounderies();
		
	public:
		Collidable(double Xdimension, double Ydimension, double Zdimension);
		~Collidable();
		
		void newPosition (cg::Vector3d postion);
		virtual bool isCollision(Collidable* obj) = 0;
		bool notify(cg::Vector3d position);
		boundaries getBoundaries();
	};
}

#endif