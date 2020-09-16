#include "global_context/kismet_global_context.h"

#include "tick/kismet_tick_manager.h"
#include "design_table/kismet_design_table_manager.h"
#include "object/kismet_object_manager.h"
#include "render/kismet_render_manager.h"
#include "input/kismet_input_manager.h"
#include "level/kismet_level_manager.h"

namespace Kismet
{
	GlobalContext g_global_context;

	void GlobalContext::startSystem()
	{
		m_tick_manager = new TickManager();
		m_design_table_manager = new DesignTableManager();
		m_object_manager = new ObjectManager();
		m_render_manager = new RenderManager();
		m_input_manager = new InputManager();
		m_level_manager = new LevelManager();
	}

	void GlobalContext::shutDownSystem()
	{
		delete m_tick_manager;
		delete m_design_table_manager;
		delete m_object_manager;
		delete m_render_manager;
		delete m_input_manager;
		delete m_level_manager;
	}

	void GlobalContext::createLevel()
	{
		m_object_manager = new ObjectManager();

		g_global_context.m_object_manager = m_object_manager;
	}

	void GlobalContext::clearLevel()
	{
		delete m_object_manager;
		m_render_manager->clearLevel();
	}

	void GlobalContext::initialize()
	{
		m_tick_manager->initialize();
		m_design_table_manager->initialize();
		m_object_manager->initialize();
		m_render_manager->initialize();
		m_input_manager->initialize();
		m_level_manager->initialize();
	}

	void GlobalContext::clear()
	{
		m_tick_manager->clear();
		m_design_table_manager->clear();
		m_object_manager->clear();
		m_render_manager->clear();
		m_input_manager->clear();
		m_level_manager->clear();
	}

	void GlobalContext::registerToGlobalContext()
	{
		g_global_context.m_tick_manager = m_tick_manager;
		g_global_context.m_design_table_manager = m_design_table_manager;
		g_global_context.m_object_manager = m_object_manager;
		g_global_context.m_render_manager = m_render_manager;
		g_global_context.m_input_manager = m_input_manager;
		g_global_context.m_level_manager = m_level_manager;
	}

}