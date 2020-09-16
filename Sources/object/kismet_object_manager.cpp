#include "object/kismet_object_manager.h"

#include "global_context/kismet_global_context.h"
#include "render/kismet_render_manager.h"
#include "level/kismet_level_manager.h"
#include "design_table/kismet_design_table_manager.h"

namespace Kismet
{
	ObjectManager::ObjectManager()
	{

	}

	ObjectManager::~ObjectManager()
	{

	}

	String ObjectManager::k_table_name = "object";
	float ObjectManager::k_my_ship_speed_times = 3.f;

	void ObjectManager::initialize()
	{
	}

	void ObjectManager::clear()
	{
		m_my_ship_object_id = 0;
	}

	void ObjectManager::tick()
	{
		// process my ship
		Ship* my_ship = &(m_ship_map[m_my_ship_object_id]);
		if (my_ship->getHealth() <= 0)
		{
			m_my_ship_live_remains--;
			g_global_context.m_render_manager->changeStringByRenderID(std::to_string(m_my_ship_live_remains), m_live_render_id);
			if (m_my_ship_live_remains >= 0)
			{
				my_ship->restoreFullHealth();
				g_global_context.m_render_manager->changeStringByRenderID(std::to_string(my_ship->getHealth()), m_health_render_id);
			}
			else
			{
				g_global_context.m_level_manager->endLevel();
				return;
			}

			my_ship->die(true);
		}
		m_my_ship_current_health = my_ship->getHealth();

		if (my_ship->isUpgradable())
		{
			my_ship->tryUpgrade();
		}
		if (!my_ship->isInMainWindow())
		{
			// TODO  my ship should not get out of main window
		}

		// process enemy ships only or (my ship and enemy ships)
		std::map<int, Ship>::iterator ship_iter;
		for (ship_iter = m_ship_map.begin(); ship_iter != m_ship_map.end(); ship_iter++)
		{
			Ship* current_ship = &ship_iter->second;

			// process enemy ships
			if (current_ship->isHostile())
			{
				if (!current_ship->isInMainWindow())  // delete object out of main window
				{
					deleteObjectBaseByID(ship_iter->first);
					continue;
				}
			}

			// process my ship and enemy ships
			if (current_ship->getHealth() <= 0)	// delete object when its health down to 0
			{
				deleteObjectBaseByID(ship_iter->first);
				continue;
			}


			current_ship->move();
			current_ship->tryFire();
		}

		// process all bullets
		std::map<int, Bullet>::iterator bullet_iter;
		for (bullet_iter = m_bullet_map.begin(); bullet_iter != m_bullet_map.end(); bullet_iter++)
		{
			Bullet* current_bullet = &bullet_iter->second;
			if (!current_bullet->isInMainWindow())  // delete object out of main window
			{
				deleteObjectBaseByID(bullet_iter->first);
				continue;
			}

			current_bullet->move();
		}

		// process other objects
		std::map<int, Object>::iterator object_iter;
		for(object_iter = m_object_map.begin(); object_iter != m_object_map.end(); object_iter++)
		{
			Object* current_object = &object_iter->second;
			
			current_object->move();
			if (current_object->isInLoop())
			{
				current_object->changePositionForLoop();
			}
		}
		
	}

	void ObjectManager::postTick()
	{
		size_t delete_object_count = m_delete_object_id_array.size();
		if (delete_object_count != 0)
		{
			for (int index = delete_object_count - 1; index >= 0; index--)    // delete must be reversed, otherwise index will be out of bounds
			{
				std::map<int, Object>::iterator object_iter = m_object_map.find(m_delete_object_id_array[index]);
				if (object_iter != m_object_map.end())
				{
					m_object_map.erase(object_iter);
				}
				std::map<int, Ship>::iterator ship_iter = m_ship_map.find(m_delete_object_id_array[index]);
				if (ship_iter != m_ship_map.end())
				{
					m_ship_map.erase(ship_iter);
				}
				std::map<int, Bullet>::iterator bullet_iter = m_bullet_map.find(m_delete_object_id_array[index]);
				if (bullet_iter != m_bullet_map.end())
				{
					m_bullet_map.erase(bullet_iter);
				}

				m_delete_object_id_array.pop_back();
			}
		}
	}

	ObjectBase* ObjectManager::getObjectBaseByID(int object_id)
	{
		if (hasObjectID(object_id))
		{
			return getObjectByID(object_id);
		}
		else if (hasShipID(object_id))
		{
			return getShipByID(object_id);
		}
		else if (hasBulletID(object_id))
		{
			return getBulletByID(object_id);
		}

		// TODO
		return nullptr;
	}

	bool ObjectManager::hasObjectID(int object_id)
	{
		std::map<int, Object>::iterator iter = m_object_map.find(object_id);
		if (iter != m_object_map.end() && &(iter->second))
		{
			return true;
		}

		return false;
	}

	Object* ObjectManager::getObjectByID(int object_id)
	{
		if (hasObjectID(object_id))
		{
			return &m_object_map[object_id];
		}

		//TODO
		return nullptr;
	}
	
	int ObjectManager::createObjectByName(const String& object_name)
	{
		if (object_name == "")
		{
			return NULL;
		}

		Object object(object_name);
		int object_id = m_object_id_allocator.allocateID(object);
		object.setObjectID(object_id);
		m_object_map[object_id] = object;

		g_global_context.m_render_manager->addObjectByID(object_id);

		return object_id;
	}

	void ObjectManager::deleteObjectBaseByID(int object_id)
	{
		m_delete_object_id_array.push_back(object_id);

		g_global_context.m_render_manager->deleteObjectByID(object_id);
	}

	bool ObjectManager::hasShipID(int object_id)
	{
		std::map<int, Ship>::iterator iter = m_ship_map.find(object_id);
		if (iter != m_ship_map.end() && &(iter->second))
		{
			return true;
		}

		return false;
	}

	Ship* ObjectManager::getShipByID(int object_id)
	{
		if (hasShipID(object_id))
		{
			return &m_ship_map[object_id];
		}

		//TODO
		return nullptr;
	}

	int ObjectManager::createShipByName(const String& ship_name)
	{
		if (ship_name == "")
		{
			return NULL;
		}

		Ship ship(ship_name);
		int object_id = m_object_id_allocator.allocateID(ship);
		ship.setObjectID(object_id);
		// check if is my ship
		if (ship.isSelf())
		{
			m_my_ship_object_id = object_id;
			m_my_ship_live_remains = 2;
		}			
		m_ship_map[object_id] = ship;

		g_global_context.m_render_manager->addObjectByID(object_id);


		return object_id;
	}

	bool ObjectManager::hasBulletID(int object_id)
	{
		std::map<int, Bullet>::iterator iter = m_bullet_map.find(object_id);
		if (iter != m_bullet_map.end() && &(iter->second))
		{
			return true;
		}

		return false;
	}

	Bullet* ObjectManager::getBulletByID(int object_id)
	{
		if (hasBulletID(object_id))
		{
			return &m_bullet_map[object_id];
		}

		//TODO
		return nullptr;
	}

	int ObjectManager::createBulletByName(const String& bullet_name)
	{
		if (bullet_name == "")
		{
			return NULL;
		}

		Bullet bullet(bullet_name);
		int object_id = m_object_id_allocator.allocateID(bullet);
		bullet.setObjectID(object_id);
		m_bullet_map[object_id] = bullet;

		g_global_context.m_render_manager->addObjectByID(object_id);

		return object_id;
	}

	void ObjectManager::processUpgradeAction()
	{
		Ship* my_ship = &(m_ship_map[m_my_ship_object_id]);
		my_ship->tryUpgrade();
		g_global_context.m_render_manager->changeStringByRenderID(std::to_string(my_ship->getHealth()), m_health_render_id);
	}

	void ObjectManager::processSuicideAction()
	{
		Ship* my_ship = &(m_ship_map[m_my_ship_object_id]);
		my_ship->changeHealth(-50);
		g_global_context.m_render_manager->changeStringByRenderID(std::to_string(my_ship->getHealth()), m_health_render_id);
		
		if (my_ship->getHealth() > 0)
		{
			my_ship->beHit(true);
		}
	}

	void ObjectManager::processFireAction()
	{
		Ship* my_ship = &(m_ship_map[m_my_ship_object_id]);
		my_ship->fire(true);
	}

	void ObjectManager::processXAxisMoveAction(float x)
	{
		Ship* my_ship = &(m_ship_map[m_my_ship_object_id]);
		my_ship->changeXAxisSpeed(k_my_ship_speed_times * x);
	}

	void ObjectManager::processYAxisMoveAction(float y)
	{
		Ship* my_ship = &(m_ship_map[m_my_ship_object_id]);
		my_ship->changeYAxisSpeed(k_my_ship_speed_times * y);
	}

	void ObjectManager::processCancelXAxisMoveAction()
	{
		Ship* my_ship = &(m_ship_map[m_my_ship_object_id]);
		my_ship->changeXAxisSpeed(0.f);
	}

	void ObjectManager::processCancelYAxisMoveAction()
	{
		Ship* my_ship = &(m_ship_map[m_my_ship_object_id]);
		my_ship->changeYAxisSpeed(0.f);
	}

}