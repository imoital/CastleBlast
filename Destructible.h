//
//  Destructible.h
//  Project
//
//  Created by Inês on 11/15/11.
//  Copyright 2011 AVT. All rights reserved.
//

#include "Collidable.h"

namespace CastleBlast {
	
	class Destructible : public Collidable 
	{
	public:
		Destructible(/*int x_min, int x_max, int y_min, int y_max, int z_min, int z_max) : 
		Collidable(x_min, x_max, y_min, y_max, z_min, z_max) {}*/);
	};
	
}