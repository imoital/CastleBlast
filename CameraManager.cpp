#include "CameraManager.h"

namespace CastleBlast 
{
	CameraManager::CameraManager(Cannon *cannon) : cg::Group("CAMERA_MANAGER")
	{
		_cannon = cannon;
	}

	CameraManager::~CameraManager(void)
	{
	}

	void CameraManager::createEntities()
	{
		_worldCamera = new WorldCamera();
		_cannonCamera = new CannonCamera(_cannon);
		addAtBeginning(_worldCamera);
		addAtBeginning(_cannonCamera);
		_isWorldCamera = true;
		_changeCameraKeyPressed = false;
	}

	void CameraManager::switchCamera()
	{
		removeAll();
		if (_isWorldCamera) {
			addAtBeginning(_cannonCamera);
			_isWorldCamera = false;
		} else {
			addAtBeginning(_worldCamera);
			_isWorldCamera = true;
		}
	}

	void CameraManager::preUpdate(unsigned long elapsed_millis) 
	{
		
		if(cg::KeyBuffer::instance()->isKeyDown('c') && !_changeCameraKeyPressed) {
			switchCamera();
			_changeCameraKeyPressed = true;
		}
		if (cg::KeyBuffer::instance()->isKeyUp('c') && _changeCameraKeyPressed) {
			_changeCameraKeyPressed = false;
		}
	}
}