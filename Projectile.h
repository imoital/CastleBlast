#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include <cg/cg.h>

#define G 9.8 // G = 9.8m/s^2

namespace CastleBlast {

	class Projectile : 
		public cg::IDrawListener
		//public cg::IUpdateListener
	{
	private:
		cg::Vector3d _position;
	public:
		cg::Vector3d _size;
		Projectile();
		~Projectile();
		void draw();
		//void update(unsigned long elapsed_millis);
		void init();
	};
}
#endif