#ifndef _KISMET_TICK_MANAGER_H_
#define _KISMET_TICK_MANAGER_H_
#include "core/kismet_prerequisites.h"

//#include <windows.h>
#include <time.h>


namespace Kismet
{
	class TickManager
	{
	public:
		TickManager();
		~TickManager();

		void initialize();
		void clear();

		void tick();
		void postTick();
		
		/*bool isGamePaused();
		void changeGamePauseState();*/

	private:

		clock_t m_time;

		//bool m_is_game_paused{ false };		// TODO
	};
}

#endif // !_KISMET_TICK_MANAGER_H_
