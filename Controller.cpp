#include "Controller.h"

namespace CastleBlast {

	Controller::Controller(void) : cg::Entity("Controller")
	{
	}

	Controller::~Controller(void)
	{
	}

	void Controller::init()
	{
	}

	void Controller::onKeyPressed(unsigned char key)
	{
		if (key == 27) {
			cg::Manager::instance()->shutdownApp();
		}
	}

	void Controller::onKeyReleased(unsigned char key)
	{
	}
	
	void Controller::onSpecialKeyPressed(int key)
	{
	}

	void Controller::onSpecialKeyReleased(int key)
	{
	}
}
