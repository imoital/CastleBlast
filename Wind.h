#ifndef WIND_H
#define WIND_H
#include <cg\cg.h>
#include <stdlib.h>
namespace CastleBlast 
{

	class Wind : 
		public cg::Entity, 
		public cg::IMouseEventListener, 
		public cg::IUpdateListener, 
		public cg::IDrawListener, 
		public cg::IReshapeEventListener
	{
	private: 
		cg::Vector3d _force;
		int MAX_FORCE;

	public:
		Wind();
		~Wind();
		
		void init();
		cg::Vector3d setWind();
		int randomBetween(int min, int max);
		cg::Vector3d getWind();
		void update(unsigned long elapsed_millis);
		void draw();
		void onReshape(int width, int height);
	};
}


#endif