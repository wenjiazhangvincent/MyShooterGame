#ifndef _KISMET_ROOT_H_
#define _KISMET_ROOT_H_

#include "core/kismet_prerequisites.h"

namespace Kismet
{
	enum class Difficulity :unsigned char
	{
		_NORMAL,
		_HARD,			// every inputing possessing inertia  (Half-Finished !!)
	};

	class Root
	{
	public:
		Root();
		~Root();

		static void initialize(int argc, char *argv[]);
		static void startGame();
		static void shutDownGame();
		static void run();
		static void clear();

	private:

	public:
		static Simple2D::Window* m_main_Window;

		static String k_main_window_name;
		static int k_main_window_width;
		static int k_main_window_height;

		static String k_design_table_directory_path;
		static String k_texture_directory_path;
		static String k_font_directory_path;

		static Difficulity m_current_difficulity;
	};


}

#endif // !_KISMET_ROOT_H_
