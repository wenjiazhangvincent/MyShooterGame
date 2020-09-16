#include "render/kismet_render_manager.h"

#include "root/kimset_root.h"
#include "global_context/kismet_global_context.h"
#include "object/kismet_object_manager.h"

namespace Kismet
{
	RenderString::RenderString(const String& str, float position_x, float position_y)
	{
		m_str = str;
		m_position = Vector2<float>(position_x, position_y);
		m_rotation = 0.f;
		m_scale = 1.f;

		m_duration = -1;
	}

	RenderManager::RenderManager()
	{

	}

	RenderManager::~RenderManager()
	{

	}

	void RenderManager::initialize()
	{

	}

	void RenderManager::clear()
	{
		destroyMainWindow();
	}

	void RenderManager::clearLevel()
	{
		m_render_object_id_array.clear();
		m_render_string_map.clear();
	}

	void RenderManager::tick(int delta_time)
	{
		for (size_t index = 0; index < m_render_object_id_array.size(); index ++ )
		{
			renderObjectByID(m_render_object_id_array[index]);
		}

		std::map<int, RenderString>::iterator iter;
		for (iter = m_render_string_map.begin(); iter != m_render_string_map.end(); iter++)
		{
			renderStringByRenderID(iter->first);
		}

		if (Simple2D::ShouldWindowClose(m_main_Window))
		{
			Root::shutDownGame();
		}
		else
		{
			Simple2D::RefreshWindowBuffer(m_main_Window);
		}
	}

	bool RenderManager::hasObjectByID(int object_id)
	{
		std::vector<int>::iterator iter = find(m_render_object_id_array.begin(), m_render_object_id_array.end(), object_id);
		return iter == m_render_object_id_array.end() ? false : true;
	}

	void RenderManager::addObjectByID(int object_id)
	{
		if (!hasObjectByID(object_id))
		{
			m_render_object_id_array.push_back(object_id);

		}
	}

	void RenderManager::deleteObjectByID(int object_id)
	{
		std::vector<int>::iterator id_iter = find(m_render_object_id_array.begin(), m_render_object_id_array.end(), object_id);
		if (id_iter != m_render_object_id_array.end())
		{
			m_render_object_id_array.erase(id_iter);
		}

	}

	int RenderManager::addString(const String& str, const float position_x, const float position_y, const float scale, const long duration)
	{
		int render_id = 0;
		RenderString render_string(str, position_x, position_y);
		render_string.m_scale = scale;
		render_string.m_duration = duration;

		render_id = m_string_render_id_allocator.allocateID(render_string);
		m_render_string_map[render_id] = render_string;

		return render_id;
	}

	void RenderManager::changeStringByRenderID(const String& str, const int render_id)
	{
		std::map<int, RenderString>::iterator iter = m_render_string_map.find(render_id);
		if (iter != m_render_string_map.end())
		{
			iter->second.m_str = str;
		}		
	}

	void RenderManager::createMainWindow(String window_name, int window_width, int window_height)
	{
		m_main_Window = Simple2D::CreateWindow(window_name, window_width, window_height);
		m_font = Simple2D::CreateFont(Root::k_font_directory_path + "AGENCYB.TTF", 20);
		window_height++;
	}

	void RenderManager::destroyMainWindow()
	{
		Simple2D::DestroyWindow(m_main_Window);
		Simple2D::DestroyFont(m_font);

		m_main_Window = nullptr;
		m_font = nullptr;
	}

	void RenderManager::renderObjectByID(int object_id)
	{	
		ObjectBase* object = g_global_context.m_object_manager->getObjectBaseByID(object_id);
		if (object != nullptr)
		{
			Simple2D::Image* image = object->getImage();
			Vector2<float>* position = object->getPosition();

			Simple2D::DrawImage(image, position->m_x, position->m_y, object->getRotation(), object->getScale());
		}
	}

	void RenderManager::renderStringByRenderID(size_t index)
	{
		RenderString render_string = m_render_string_map[index];
		Simple2D::DrawString(m_font, render_string.m_str, render_string.m_position.m_x, render_string.m_position.m_y, render_string.m_rotation, render_string.m_scale);
	}

}