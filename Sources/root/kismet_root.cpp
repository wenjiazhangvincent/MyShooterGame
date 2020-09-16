#include "root/kimset_root.h"

#include "global_context/kismet_global_context.h"
#include "tick/kismet_tick_manager.h"
#include "render/kismet_render_manager.h"

namespace Kismet
{
	Simple2D::Window* Root::m_main_Window = nullptr;
	String Root::k_main_window_name = "ShooterGame";
	int Root::k_main_window_width = 1600;
	int Root::k_main_window_height = 600;

	String Root::k_design_table_directory_path = "./../../Content/DesignTables/";
	String Root::k_texture_directory_path = "./../../Content/Textures/";
	String Root::k_font_directory_path = "./../../Content/Fonts/";

	Difficulity Root::m_current_difficulity = Difficulity::_NORMAL;
	//Difficulity Root::m_current_difficulity = Difficulity::_HARD;

	Root::Root()	
	{
	}

	Root::~Root()
	{

	}

	void Root::initialize(int argc, char *argv[])
	{
		g_global_context.initialize();

		g_global_context.m_render_manager->createMainWindow(k_main_window_name, k_main_window_width, k_main_window_height);
	}

	void Root::startGame()
	{
		g_global_context.startSystem();
	}

	void Root::shutDownGame()
	{
		g_global_context.shutDownSystem();
	}

	void Root::run()
	{
		while (true)
		{
			g_global_context.m_tick_manager->tick();
			g_global_context.m_tick_manager->postTick();
		}
	}

	void Root::clear()
	{
		g_global_context.clear();
	}

}