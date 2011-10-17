#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <cg/cg.h>
#include "CameraManager.h"
#include "DebugManager.h"

namespace CastleBlast {
	class Controller : 
		public cg::Entity,
		public cg::IKeyboardEventListener,
		public cg::IMouseEventListener
	{
	private:
	/*	void specialKeyPressed(int key);
		void specialKeyReleased(int key);
		void keypressed(int key);
		void keyReleased(int key);*/
		bool _F2Pressed;
	public:
		Controller(void);
		~Controller(void);
		void init();
		void onKeyPressed(unsigned char key);
		void onKeyReleased(unsigned char key);
		void onSpecialKeyPressed(int key);
		void onSpecialKeyReleased(int key);

	};
}

#endif

