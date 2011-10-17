#include "Projectile.h"

namespace CastleBlast {

	Projectile::Projectile(void)
	{
		_size = cg::Vector3d(5, 15, 3); 
		_position = cg::Vector3d(10.0, 10.0, 10.0);
	}


	Projectile::~Projectile(void)
	{
	}

	void Projectile::init()
	{
	}

	void Projectile::draw()
	{
		cg::Vector3d min = _position - _size;
		cg::Vector3d max = _position + _size;
		glPushMatrix();
			glTranslatef(10, 10, 10);
			glutSolidSphere(1, 16, 16);
		glPopMatrix();
/*		glBegin(GL_QUADS);
			
			glVertex3d(0, 0, 0);
			glVertex3d(0, 0, 10);
			glVertex3d(0, 10, 10);
			glVertex3d(0, 10, 0);
		glEnd();
			glVertex3d(min[0], min[1], min[2]);
			glVertex3d(max[0], min[0], min[2]);
			glVertex3d(max[0], max[1], min[2]);
			glVertex3d(min[0], max[1], min[2]);

			glVertex3d(min[0], min[1], max[2]);
			glVertex3d(max[0], min[1], max[2]);
			glVertex3d(max[0], max[1], max[2]);
			glVertex3d(min[0], max[1], max[2]);

			glVertex3d(min[0], min[1], min[2]);
			glVertex3d(max[0], min[1], min[2]);
			glVertex3d(max[0], min[1], max[2]);
			glVertex3d(min[0], min[1], max[2]);

			glVertex3d(min[0], min[1], min[2]);
			glVertex3d(min[0], max[1], min[2]);
			glVertex3d(min[0], max[1], max[2]);
			glVertex3d(min[0], min[1], max[2]);

			glVertex3d(min[0], min[1], min[2]);
			glVertex3d(min[0], min[1], max[2]);
			glVertex3d(min[0], max[1], max[2]);
			glVertex3d(min[0], max[1], min[2]);

			glVertex3d(max[0], min[1], min[2]);
			glVertex3d(max[0], min[1], max[2]);
			glVertex3d(max[0], max[1], max[2]);
			glVertex3d(max[0], max[1], min[2]);*/
//		glEnd();
	}
				
}
