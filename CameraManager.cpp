#include "CameraManager.h"

namespace CastleBlast 
{
	CameraManager::CameraManager(Cannon *cannon) : cg::Entity("CAMERA_MANAGER")
	{
		_cannon = cannon;
	}

	CameraManager::~CameraManager(void)
	{
	}

	void CameraManager::init()
	{
		_cameras.push_back(new WorldCamera());
		_cameras.push_back(new CannonCamera(_cannon));
		for (int i = 0; i < _cameras.size(); i++)
			_cameras[i]->init();
		_isWorldCamera = true;
		_changeCameraKeyPressed = false;
		_activeCamera = 0;
	}

	void CameraManager::switchCamera()
	{
		_activeCamera = (_activeCamera+1)%_cameras.size();
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

	void CameraManager::update(unsigned long elapsed_millis) 
	{
		_cameras[_activeCamera]->update(elapsed_millis);
	}
	
	void CameraManager::draw()
	{
		_cameras[_activeCamera]->draw();
	}

	void CameraManager::setCannonCameraRotation(int rot)
	{
		for (int i = 0; i < _cameras.size(); i++) {
			CannonCamera* cannonCamera = dynamic_cast<CannonCamera*>(_cameras[i]);
			if(cannonCamera != 0) {
				cannonCamera->setInitialRotation(rot);
				return;
			}
		}
	}
	
	void CameraManager::onReshape(int width, int height)
	{
		_cameras[_activeCamera]->onReshape(width, height);
	}
	
	void CameraManager::onMouse(int button, int state, int x, int y)
	{
		_cameras[_activeCamera]->onMouse(button, state, x, y);
	}
	void CameraManager::onMouseMotion(int x, int y) 
	{
		_cameras[_activeCamera]->onMouseMotion(x, y);
	}
	void CameraManager::onMousePassiveMotion(int x, int y)
	{
		_cameras[_activeCamera]->onMousePassiveMotion(x, y);
	}
	
	void CameraManager::drawOverlay()
	{
		_cameras[_activeCamera]->drawOverlay();
	}
	
	void CameraManager::setLineColor(double r, double g, double b)
	{
		for (int i = 0; i < _cameras.size(); i++) {
			CannonCamera* cannonCamera = dynamic_cast<CannonCamera*>(_cameras[i]);
			if(cannonCamera != 0) {
				cannonCamera->setLineColor(r, g, b);
				return;
			}
		}
	}
}