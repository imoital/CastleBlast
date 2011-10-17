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
}