#ifndef CAMERAMANAGER_H_
#define CAMERAMANAGER_H_

#include "cg/cg.h"
#include "WorldCamera.h"
namespace CastleBlast 
{
	class CameraManager : 
		public cg::Entity,
		public cg::IDrawListener
	{
	private:
		std::vector<WorldCamera*> _cameraVector;
		WorldCamera* _worldCamera;
		typedef std::vector<WorldCamera*>::iterator _worldCameraIterator;
	public:
		CameraManager(void);
		~CameraManager(void);
		void switchCamera();
		void init();
		void draw();
	};
}
#endif