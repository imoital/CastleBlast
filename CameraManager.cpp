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
		//_worldCamera = new WorldCamera();
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
			//_worldCamera->setPos(_cannonCamera->getEpos(), _cannonCamera->getCpos(), _cannonCamera->getUpos());
			_isWorldCamera = true;
		}
	}

	WorldCamera* CameraManager::getWorldCamera(){
		return _worldCamera;
	}

	bool CameraManager::isWorldCamera(){
		return _isWorldCamera;
	}

	Cannon* CameraManager::getCannon(){
		return _cannon;
	}

	void CameraManager::setWorldCamera(WorldCamera* w){
		_worldCamera = w;
	}

	void CameraManager::preUpdate(unsigned long elapsed_millis) 
	{
	}
	
	void CameraManager::postInit()
	{
		remove(_cannonCamera->getId());
	}

	void CameraManager::setCannonCameraRotation(int rot)
	{
		_cannonCamera->setInitialRotation(rot);
	}
}