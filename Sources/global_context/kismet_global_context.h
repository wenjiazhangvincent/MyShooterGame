#ifndef _KISMET_GLOBAL_CONTEXT_H_
#define _KISMET_GLOBAL_CONTEXT_H_

namespace Kismet
{
	class GlobalContext
	{
	public:

		void startSystem();
		void shutDownSystem();

		void createLevel();
		void clearLevel();

		void initialize();
		void clear();

		void registerToGlobalContext();

	private:

	public:
		class RandomAllocator* m_random_allocator;

		class TickManager* m_tick_manager = nullptr;
		class DesignTableManager* m_design_table_manager = nullptr;
		class ObjectManager* m_object_manager = nullptr;
		class RenderManager* m_render_manager = nullptr;
		class InputManager* m_input_manager = nullptr;
		class LevelManager* m_level_manager = nullptr;

	};

	extern GlobalContext g_global_context;
}

#endif // !_KISMET_GLOBAL_CONTEXT_H_
