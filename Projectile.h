#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include <cg/cg.h>
#include "DebugMode.h"

#define G 9.8 // G = 9.8m/s^2

namespace CastleBlast {

	class Projectile : 
		public DebugMode
	{
	private:
		cg::Vector3d _position;
		bool _debug;
		cg::Vector3d _front, _up, _right;
	public:
		cg::Vector3d _size;
		
		Projectile();
		~Projectile();
		void draw();
		void debugDrawAxis();
		void debugToggle();
	};
}
#endif