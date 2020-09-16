#include "object/kismet_object_base.h"

#include "object/kismet_object_manager.h"
#include "global_context/kismet_global_context.h"
#include "design_table/kismet_design_table_manager.h"
#include "root/kimset_root.h"

namespace Kismet
{
	ObjectBase::ObjectBase(const String& object_name)
	{
		m_object_name = object_name;

		String file_name = g_global_context.m_design_table_manager->getStringByName(m_object_name, ObjectManager::k_table_name, "file_name");
		Simple2D::Image* image = Simple2D::CreateImage(Root::k_texture_directory_path + file_name + ".png");
		m_image = image;

		Vector2<int> size;
		Simple2D::GetImageSize(image, &size.m_x, &size.m_y);
		m_size = size;

		m_rotation = g_global_context.m_design_table_manager->getFloatByName(m_object_name, ObjectManager::k_table_name, "rotation");
		m_scale = g_global_context.m_design_table_manager->getFloatByName(m_object_name, ObjectManager::k_table_name, "scale");
		m_speed.m_x = g_global_context.m_design_table_manager->getFloatByName(m_object_name, ObjectManager::k_table_name, "speed_x");
		m_speed.m_y = g_global_context.m_design_table_manager->getFloatByName(m_object_name, ObjectManager::k_table_name, "speed_y");
		m_damage = g_global_context.m_design_table_manager->getIntByName(m_object_name, ObjectManager::k_table_name, "damage");
		m_is_deleted_after_colliding = g_global_context.m_design_table_manager->getBoolByName(m_object_name, ObjectManager::k_table_name, "is_deleted_after_colliding");
		m_duration = g_global_context.m_design_table_manager->getIntByName(m_object_name, ObjectManager::k_table_name, "duration");
		m_is_in_loop = g_global_context.m_design_table_manager->getBoolByName(m_object_name, ObjectManager::k_table_name, "is_in_loop");
		int team_id = g_global_context.m_design_table_manager->getIntByName(object_name, ObjectManager::k_table_name, "team_id");
		setTeamID(team_id);

	}

	void ObjectBase::setObjectID(int object_id)
	{
		m_object_id = object_id;
	}

	Simple2D::Image* ObjectBase::getImage()
	{
		return m_image;
	}

	void ObjectBase::setSpeed(float x, float y)
	{
		m_speed.m_x = x;
		m_speed.m_y = y;
	}

	void ObjectBase::move()
	{
		m_position += m_speed;
	}

	bool ObjectBase::isInMainWindow()
	{
		float m_left = m_position.m_x - m_size.m_x / 2;
		float m_right = m_position.m_x + m_size.m_x / 2;
		float m_top = m_position.m_y + m_size.m_y / 2;
 		float m_bottom = m_position.m_y - m_size.m_y / 2;
	
		bool flag_x = (max(m_left, 0) > min(m_right, Root::k_main_window_width)) ? true : false;
		bool flag_y = (max(m_bottom, 0) > min(m_top, Root::k_main_window_height)) ? true : false;
		return !(flag_x ^ flag_y);
	}

	void ObjectBase::setPosition(float position_x, float position_y)
	{
		m_position.m_x = position_x;
		m_position.m_y = position_y;
	}

	Vector2<float>* ObjectBase::getPosition()
	{
		return &m_position;
	}

	float ObjectBase::getRotation()
	{
		return m_rotation;
	}

	float ObjectBase::getScale()
	{
		return m_scale;
	}

	void ObjectBase::setTeamID(int int_team_id)
	{
		if (int_team_id < 0 || int_team_id >= int(TeamID::_COUNT))
		{
			m_team_id = TeamID::_TEAM_NEUTRAL;
		}
		else
		{
			m_team_id = TeamID(int_team_id);
		}
	}

	TeamID ObjectBase::getTeamID()
	{
		return m_team_id;
	}

	bool ObjectBase::isNeutral()
	{
		return m_team_id == TeamID::_TEAM_NEUTRAL;
	}

	bool ObjectBase::isSelf()
	{
		return m_team_id == TeamID::_TEAM_SELF;
	}

	bool ObjectBase::isHostile()
	{
		return m_team_id == TeamID::_TEAM_HOSTILE;
	}

	void ObjectBase::setDamage(const int damage)		// if damage's type is unsigned int, which will turn into positive even if you pass a negative number 
	{
		if (damage < 0)
		{
			m_damage = 0;
		}
		else
		{
			m_damage = damage;
		}
	}

	unsigned int ObjectBase::getDamege()
	{
		return m_damage;
	}

	bool ObjectBase::isInLoop()
	{
		return m_is_in_loop;
	}

	void ObjectBase::changePositionForLoop()
	{
		if (m_position.m_x + m_size.m_x < Root::k_main_window_width)
		{
			m_position.m_x = float(Root::k_main_window_width);
		}
	}

}