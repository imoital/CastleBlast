#include "CameraManager.h"

namespace CastleBlast 
{
	CameraManager::CameraManager(void) : cg::Entity("CAMERA_MANAGER")
	{
	}

	CameraManager::~CameraManager(void)
	{
	}

	void CameraManager::init()
	{
		_worldCamera = new WorldCamera();
		_worldCamera->init();
		//addAtBeginning(_camera);
	}

	void CameraManager::switchCamera()
	{
	}

	void CameraManager::draw()
	{
		_worldCamera->draw();
	}

	void CameraManager::update(unsigned long elapsed_millis)
	{
		_worldCamera->update(elapsed_millis);
	}
	
	void CameraManager::onMouse(int button, int state, int x, int y){
		_worldCamera->onMouse(button, state, x, y);
	}
	void CameraManager::onMouseMotion(int x, int y){
		_worldCamera->onMouseMotion(x, y);
	}
	 void CameraManager::onMousePassiveMotion(int x, int y){
		_worldCamera->onMousePassiveMotion(x,y);
	}
}