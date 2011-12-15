#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include <cg/cg.h>
#include "DebugMode.h"
#include "Collidable.h"

#define G 13 // G = 9.8m/s^2

namespace CastleBlast {

	class GameManager;
	class Wind;

	class Projectile : public DebugMode, public Collidable
	{
	private:
		cg::Vector3d _position;
		bool _debug;
		cg::Vector3d _front, _up, _right;
		cg::Vector3d _velocity, _windForce;
		cg::Vector3d _startPosition;
		int _force;
		bool _start;
		bool _isOtherPlayer;
		GameManager* _gameManager;
		Wind* _wind;
		
	public:
		cg::Vector3d _size;
		
		Projectile(GameManager* gm);
		~Projectile();
		void init();
		void draw();
		void update(cg::Vector3d poistion, cg::Vector3d rotation, double force, unsigned long elapsed_millis);
		void debugDrawAxis();
		void debugToggle();
		void start();
		bool isCollision(Collidable *obj);
		bool getIsOtherPlayer();
		void toggleIsOtherPlayer();
		bool hasStart();
	};
}
#endif