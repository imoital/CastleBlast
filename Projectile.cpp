#include "Projectile.h"

namespace CastleBlast {

	Projectile::Projectile()
	{
		_size = cg::Vector3d(5, 15, 3); 
		_position = cg::Vector3d(10.0, 10.0, 10.0);
		_debug = false;
		_start = false;
		_front.set(2,0,0);
		_up.set(0,2,0);
		_right.set(0,0,2);
	}


	Projectile::~Projectile(void)
	{}
	
	void Projectile::init() {}

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
		{
			glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);
			glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
			
			glTranslated(_position[0], _position[1], _position[2]);
			
			if(_debug)
				debugDrawAxis();

			glutSolidSphere(0.5, 16, 16);
		}
		glPopMatrix();
	}

	void Projectile::debugDrawAxis()
	{
		if (_debug){
			glDisable(GL_LIGHTING);
			glColor3f(1.0f,0.0f,0.0f);
			glBegin(GL_LINES);
			{
				glVertex3d(0.0,0.0,0.0);
				glVertex3d(_front[0],_front[1],_front[2]);
			}
			glEnd();
			glColor3f(0.0f,1.0f,0.0f);
			glBegin(GL_LINES);
			{
				glVertex3d(0.0,0.0,0.0);
				glVertex3d(_up[0],_up[1],_up[2]);
			}
			glEnd();
			glColor3f(0.0f,0.0f,1.0f);
			glBegin(GL_LINES);
			{
				glVertex3d(0.0,0.0,0.0);
				glVertex3d(_right[0],_right[1],_right[2]);
			}
			glEnd();
			glEnable(GL_LIGHTING);
		}
	}

	void Projectile::debugToggle()
	{
		_debug = !_debug;
	}
	
	void Projectile::update(cg::Vector3d position, float rotation, unsigned long elapsed_millis) 
	{
		if (!_start){
			float radRotation = (rotation*3.14)/(float)180 + 0.79;
			_position = position;
			_position[1] = _position[1] + 7*sin(radRotation);
			_position[2] = _position[2] + 7*cos(radRotation);
			_direction = cg::Vector3d(0, sin(radRotation), cos(radRotation));
		}
		else {
			_position += _direction;
			_position[1] -= G*elapsed_millis*0.0015;
			std::cout << "direction " << _direction << std::endl;
			std::cout << "gravity " << G*elapsed_millis*0.0015 << std::endl;
			std::cout << "position " << _position << std::endl;
		}
	}
	
	void Projectile::start()
	{
		_start = true;
	}
				
}
