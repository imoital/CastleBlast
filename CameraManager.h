#ifndef CAMERAMANAGER_H_
#define CAMERAMANAGER_H_

#include "cg/cg.h"
#include "WorldCamera.h"
#include "CannonCamera.h"
#include "Cannon.h"
#include "Sky.h"
#include "Camera.h"

namespace CastleBlast 
{
	class CameraManager : 
		public cg::Entity, public cg::IDrawListener,
	public cg::IUpdateListener, public cg::IMouseEventListener, public cg::IReshapeEventListener
	{
	private:
		std::vector<WorldCamera*> _cameraVector;
		WorldCamera* _worldCamera;
		CannonCamera* _cannonCamera;
		bool _changeCameraKeyPressed;
		typedef std::vector<WorldCamera*>::iterator _worldCameraIterator;
		bool _isWorldCamera;
		Cannon *_cannon;
		std::vector<Camera*> _cameras;
		int _activeCamera;
	
	public:
		CameraManager(Cannon *cannon);
		~CameraManager(void);
		void init();
		void switchCamera();
		void update(unsigned long elapsed_millis);
		void setCannonCameraRotation(int rot);
		void postInit();
		void draw();
		WorldCamera* getWorldCamera();
		bool isWorldCamera();
		Cannon* getCannon();
		void onReshape(int width, int height);
		void onMouse(int button, int state, int x, int y);
		void onMouseMotion(int x, int y);
		void onMousePassiveMotion(int x, int y);
		void drawOverlay();
		void setLineColor(double r, double g, double b);
	};
}
#endif