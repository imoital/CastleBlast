#ifndef CAMERAMANAGER_H_
#define CAMERAMANAGER_H_

#include "cg/cg.h"
#include "WorldCamera.h"
#include "CannonCamera.h"
#include "Cannon.h"

namespace CastleBlast 
{
	class CameraManager : 
		public cg::Group, public cg::GroupDraw,
		public cg::GroupUpdate, public cg::GroupMouseEvent
	{
	private:
		std::vector<WorldCamera*> _cameraVector;
		WorldCamera* _worldCamera;
		CannonCamera* _cannonCamera;
		bool _changeCameraKeyPressed;
		typedef std::vector<WorldCamera*>::iterator _worldCameraIterator;
		bool _isWorldCamera;
		Cannon *_cannon;
	
	public:
		CameraManager(Cannon *cannon);
		~CameraManager(void);
		void createEntities();
		void switchCamera();
		void preUpdate(unsigned long elapsed_millis);
		void setCannonCameraRotation(int rot);
		
	};
}
#endif