#include "object/kismet_ship.h"

#include "object/kismet_object_manager.h"
#include "global_context/kismet_global_context.h"
#include "design_table/kismet_design_table_manager.h"
#include "level/kismet_level_manager.h"
#include "render/kismet_render_manager.h"

namespace Kismet
{

	Ship::Ship(const String& ship_name):ObjectBase(ship_name)
	{
		m_bullet_name = g_global_context.m_design_table_manager->getStringByName(m_object_name, ObjectManager::k_table_name, "bullet_name");
		m_fire_chance = g_global_context.m_design_table_manager->getIntByName(m_object_name, ObjectManager::k_table_name, "fire_chance");
		m_health = g_global_context.m_design_table_manager->getIntByName(m_object_name, ObjectManager::k_table_name, "health");
		m_experience = g_global_context.m_design_table_manager->getIntByName(m_object_name, ObjectManager::k_table_name, "experience");
		m_level_up_exp = g_global_context.m_design_table_manager->getIntByName(m_object_name, ObjectManager::k_table_name, "level_up_exp");
		m_next_level_name = g_global_context.m_design_table_manager->getStringByName(m_object_name, ObjectManager::k_table_name, "next_level_name");
	}

	void Ship::fire(bool is_my_ship)
	{
		float fire_position_x, fire_position_y;
		if (is_my_ship)
		{
			fire_position_x = m_position.m_x + 0.5f * m_size.m_x;		// these variables should be stored in design tables
			fire_position_y = m_position.m_y;
		}
		else
		{
			fire_position_x = m_position.m_x - 0.5f * m_size.m_x;
			fire_position_y = m_position.m_y;
		}

		g_global_context.m_level_manager->createObjectByNameAndPosition(m_bullet_name, fire_position_x, fire_position_y);
	}

	void Ship::tryFire()
	{
		int random_number = g_global_context.m_random_allocator->generate(10000);
		if (random_number >= 0 && random_number < m_fire_chance)
		{
			fire(false);
		}
	}

	void Ship::beHit(bool is_my_ship)
	{
		float hit_position_x, hit_position_y;
		if (is_my_ship)
		{
			hit_position_x = m_position.m_x + 0.5f * m_size.m_x;		// these variables should be stored in design tables
			hit_position_y = m_position.m_y;
		}
		else
		{
			hit_position_x = m_position.m_x - 0.5f * m_size.m_x;
			hit_position_y = m_position.m_y;
		}
		g_global_context.m_level_manager->createObjectByNameAndPosition("Explosion_1", hit_position_x, hit_position_y);
	}

	void Ship::die(bool is_my_ship)
	{
		float die_position_x, die_position_y;
		if (is_my_ship)
		{
			die_position_x = m_position.m_x + 0.5f * m_size.m_x;		// these variables should be stored in design tables
			die_position_y = m_position.m_y;
		}
		else
		{
			die_position_x = m_position.m_x - 0.5f * m_size.m_x;
			die_position_y = m_position.m_y;
		}
		g_global_context.m_level_manager->createObjectByNameAndPosition("Explosion_2", die_position_x, die_position_y);
	}

	bool Ship::isUpgradable()
	{
		if (m_next_level_name != "" && m_experience >= m_level_up_exp)
		{
			return true;
		}

		return false;
	}

	void Ship::upgrade()
	{
		m_experience -= m_level_up_exp;
		if (m_experience < 0)
		{
			m_experience = 0;
		}

		m_object_name = m_next_level_name;

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

		m_bullet_name = g_global_context.m_design_table_manager->getStringByName(m_object_name, ObjectManager::k_table_name, "bullet_name");
		m_health = g_global_context.m_design_table_manager->getIntByName(m_object_name, ObjectManager::k_table_name, "health");
		m_level_up_exp = g_global_context.m_design_table_manager->getIntByName(m_object_name, ObjectManager::k_table_name, "level_up_exp");
		m_next_level_name = g_global_context.m_design_table_manager->getStringByName(m_object_name, ObjectManager::k_table_name, "next_level_name");

		float m_upgrade_position_x = m_position.m_x + 0.5f * m_size.m_x;
		float m_upgrade_position_y = m_position.m_y + 1.5f * m_size.m_y;
		g_global_context.m_level_manager->createObjectByNameAndPosition("Upgrade", m_upgrade_position_x, m_upgrade_position_y);
	}

	void Ship::tryUpgrade()
	{
		if (m_next_level_name != "")
		{
			upgrade();
		}
	}

	void Ship::changePositionRelatively(float x, float y)
	{
		m_position.m_x += x;
		m_position.m_y += y;
	}

	void Ship::changeXAxisSpeed(float x)
	{
		m_speed.m_x = x;
	}

	void Ship::changeYAxisSpeed(float y)
	{
		m_speed.m_y = y;
	}

	void Ship::setHealth(const int health)
	{
		int full_health = g_global_context.m_design_table_manager->getIntByName(m_object_name, ObjectManager::k_table_name, "health");
		if (health < 0)
		{
			m_health = 0;
		}
		else if(health >= full_health)
		{
			m_health = full_health;
		}
		else
		{
			m_health = health;
		}
	}

	void Ship::changeHealth(const int delta_health)
	{
		setHealth(m_health + delta_health);
	}

	void Ship::restoreFullHealth()
	{
		m_health = g_global_context.m_design_table_manager->getIntByName(m_object_name, ObjectManager::k_table_name, "health");
	}

	int Ship::getHealth()
	{
		return m_health;
	}

}