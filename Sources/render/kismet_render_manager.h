#ifndef _KISMET_RENDER_MANAGER_H_
#define _KISMET_RENDER_MANAGER_H_
#include "core/kismet_prerequisites.h"
#include "object/kismet_object_base.h"

namespace Kismet
{
	class RenderString
	{
	public:
		RenderString() {};
		~RenderString() {};
		RenderString(const String& str, float position_x, float position_y);
		
		String m_str;
		Vector2<float> m_position;
		float m_rotation;
		float m_scale;

		long m_duration;
;	};

	class RenderManager
	{
	public:
		RenderManager();
		~RenderManager();

		void initialize();
		void clear();
		void clearLevel();

		void tick(int delta_time);

		bool hasObjectByID(int object_id);
		Simple2D::Image* getObjectByID(int object_id);
		void addObjectByID(int object_id);
		void deleteObjectByID(int object_id);

		int addString(const String& str, const float position_x, const float position_y, const float scale, const long duration);
		void changeStringByRenderID(const String& str, const int render_id);

		void createMainWindow(String window_name, int window_width, int window_height);
		void destroyMainWindow();

		void renderObjectByID(int object_id);
		//void renderString(const String& str, float position_x, float position_y);
		void renderStringByRenderID(size_t index);


	private:
		Simple2D::Window* m_main_Window;
		Simple2D::Font* m_font;

		std::vector<int> m_render_object_id_array;

		IDAllocator<RenderString> m_string_render_id_allocator;
		std::map<int, RenderString> m_render_string_map;
	};

}

#endif // !_KISMET_RENDER_MANAGER_H_
