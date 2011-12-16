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
		_F2Pressed = false;
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
		if (key == GLUT_KEY_F2) {
			DebugManager *debugManager = (DebugManager*) cg::Registry::instance()->get("DEBUG_MANAGER");
			if (debugManager) {
				debugManager->debugToggle();
			}
		}
	}
}
