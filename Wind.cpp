#include "Wind.h"
#include <math.h>

namespace CastleBlast 
{
	Wind::Wind() : cg::Entity("WIND")
	{
	}

	Wind::~Wind()
	{
	}

	void Wind::init()
	{
		MAX_FORCE = cg::Properties::instance()->getInt("MAX_WIND");
		_force = setWind();
	}

	cg::Vector3d Wind::getWind()
	{
		return _force;
	}

	cg::Vector3d Wind::setWind()
	{
		int windForce = MAX_FORCE;
		_force[0] = randomBetween(-windForce, windForce);
		_force[1] = 0;//randomBetween(-windForce, windForce);
		//_force[2] = randomBetween(-windForce, windForce);
		return _force/10;
	}

	int Wind::randomBetween(int min, int max)
	{
		return (rand() / (double)RAND_MAX * (max-min)) + min;
	}

	void Wind::update(unsigned long elapsed_millis){}

	void Wind::draw(){}

	void Wind::onReshape(int width, int height){}


}

