#include "tick/kismet_tick_manager.h"

#include "global_context/kismet_global_context.h"
#include "render/kismet_render_manager.h"
#include "input/kismet_input_manager.h"
#include "object/kismet_object_manager.h"
#include "level/kismet_level_manager.h"

namespace Kismet
{
	TickManager::TickManager()
	{

	}

	TickManager::~TickManager()
	{

	}

	void TickManager::initialize()
	{
		m_time = clock();
		//m_time = Simple2D::GetGameTime();			// i didn't choose GetGameTime function because it's not in millisecond level
	}

	void TickManager::clear()
	{
	}

	void TickManager::tick()
	{
		clock_t current_time = clock();
		//long current_time = Simple2D::GetGameTime();
		int delta_time = int(long(current_time) - m_time);		// both of them are unsigned long, which should be transfered to long first, then to int
		m_time = current_time;

		g_global_context.m_input_manager->tick();

		g_global_context.m_object_manager->tick();
		g_global_context.m_render_manager->tick(delta_time);		// process permanent rendering and temporary rendering (unfinished)
		g_global_context.m_level_manager->tick();

		//if (!isGamePaused())
		//{
		//	g_global_context.m_object_manager->tick();
		//	g_global_context.m_render_manager->tick(delta_time);		// process permanent rendering and temporary rendering (unfinished)
		//	g_global_context.m_level_manager->tick();

		//}

		//std::cout << delta_time << std::endl;
	}


	void TickManager::postTick()
	{
		g_global_context.m_object_manager->postTick();
	}

	/*bool TickManager::isGamePaused()
	{
		return m_is_game_paused;
	}

	void TickManager::changeGamePauseState()
	{
		m_is_game_paused = !m_is_game_paused;
	}*/

}