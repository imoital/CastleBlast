#include "Projectile.h"

namespace CastleBlast {

	Projectile::Projectile() : Collidable(0.7, 0.7, 0.7)
	{
		_size = cg::Vector3d(5, 15, 3); 
		_position = cg::Vector3d(10.0, 10.0, 10.0);
		_debug = false;
		_start = false;
		_front.set(2,0,0);
		_up.set(0,2,0);
		_right.set(0,0,2);
		_force = 40;
	}


	Projectile::~Projectile(void)
	{}
	
	void Projectile::init() 
	{
		_isOtherPlayer = false;
	}

	void Projectile::draw()
	{
		
		cg::Vector3d min = _position - _size;
		cg::Vector3d max = _position + _size;
		
		GLfloat mat_emission[] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat mat_ambient[] = {0.25f,0.25f,0.25f,1.0f};
		GLfloat mat_diffuse[] = {0.4f,0.4f,0.4f,1.0f};
		GLfloat mat_specular[] = {0.774f,0.774f,0.774f,1.0f};
		GLfloat mat_shininess[] = {76.8f};
		
		glPushMatrix();
		{
			glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);
			glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
			
			if (_start && _debug)
				drawBoundingBox();
			
			glTranslated(_position[0], _position[1], _position[2]);
			
			if (_start) {
				if(_debug)
					debugDrawAxis();
				
				glutSolidSphere(0.7, 16, 16);
			}
		}
		glPopMatrix();
	}

	void Projectile::toggleIsOtherPlayer()
	{
		_isOtherPlayer = !_isOtherPlayer;
	}

	bool Projectile::getIsOtherPlayer()
	{
		if (_isOtherPlayer == true) {
			_isOtherPlayer = false;
			return true;
		} else
			return _isOtherPlayer;
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
	
	void Projectile::update(cg::Vector3d position, cg::Vector3d direction, unsigned long elapsed_millis) 
	{
		if (!_start){
			_position = position;
			_position[1] = _position[1]+3;
			_direction = direction;
			_direction[1] = _direction[1]+0.5;
			_direction = _direction*_force;
		}
		else {
			
			double time = (elapsed_millis / 1000.0);
			
			_direction[1] += -G*time;
			_position[1] += _direction[1] * time - (G*time*time)/2;
			_position[0] += _direction[0]*time;
			_position[2] += _direction[2]*time;
			if (notify(_position)) {
				_start = false;
				_isOtherPlayer = true;
			}
		}
	}
	
	void Projectile::start()
	{
		_start = true;
	}
	
	bool Projectile::isCollision(CastleBlast::Collidable *obj)
	{
		Collidable::boundaries otherBoundaries = obj->getBoundaries();
		
		if ((_boundes.x_min >= otherBoundaries.x_min) &&
		    (_boundes.x_max <= otherBoundaries.x_max) &&
		    (_boundes.y_min >= otherBoundaries.y_min) &&
		    (_boundes.y_max <= otherBoundaries.y_max) &&
		    (_boundes.z_min >= otherBoundaries.z_min) &&
		    (_boundes.z_max <= otherBoundaries.z_max)) {
			_start = false;
			return true;
		}
		else return false;
	}
}
