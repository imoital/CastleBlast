#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include <cg/cg.h>
#include "DebugMode.h"

#define G 9.8 // G = 9.8m/s^2

namespace CastleBlast {

	class Projectile : public DebugMode
	{
	private:
		cg::Vector3d _position;
		bool _debug;
		cg::Vector3d _front, _up, _right;
		cg::Vector3d _direction;
		cg::Vector3d _startPosition;
		int _force;
		bool _start;
		
	public:
		cg::Vector3d _size;
		
		Projectile();
		~Projectile();
		void init();
		void draw();
		void update(cg::Vector3d poistion, float rotation, unsigned long elapsed_millis);
		void debugDrawAxis();
		void debugToggle();
		void start();
	};
}
#endif