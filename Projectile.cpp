#include "Projectile.h"

namespace CastleBlast {

	Projectile::Projectile(void)
	{
		_size = cg::Vector3d(5, 15, 3); 
		_position = cg::Vector3d(10.0, 10.0, 10.0);
		_debug = OFF;
		_front.set(2,0,0);
		_up.set(0,2,0);
		_right.set(0,0,2);
	}


	Projectile::~Projectile(void)
	{}

	void Projectile::draw()
	{
		
		cg::Vector3d min = _position - _size;
		cg::Vector3d max = _position + _size;
		
		GLfloat mat_emission[] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat mat_ambient[] = {0.3f,0.3f,0.1f,1.0f};
		GLfloat mat_diffuse[] = {0.9f,0.9f,0.1f,1.0f};
		GLfloat mat_specular[] = {0.9f,0.9f,0.9f,1.0f};
		GLfloat mat_shininess[] = {100.0f};
		
		glPushMatrix();
		
			glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);
			glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

			glTranslatef(0, 0, 0);
		
			if (_debug){
				glDisable(GL_LIGHTING);
				glColor3f(1.0f,0.0f,0.0f);
				glBegin(GL_LINES);
					glVertex3d(0.0,0.0,0.0);
					glVertex3d(_front[0],_front[1],_front[2]);
				glEnd();
				glColor3f(0.0f,1.0f,0.0f);
				glBegin(GL_LINES);
					glVertex3d(0.0,0.0,0.0);
					glVertex3d(_up[0],_up[1],_up[2]);
				glEnd();
				glColor3f(0.0f,0.0f,1.0f);
				glBegin(GL_LINES);
					glVertex3d(0.0,0.0,0.0);
					glVertex3d(_right[0],_right[1],_right[2]);
				glEnd();
				glEnable(GL_LIGHTING);
			}
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
	
	void Projectile::toggleDebug()
	{
		_debug = !_debug;
	}
				
}
