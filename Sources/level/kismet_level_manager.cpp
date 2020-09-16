#include "level/kismet_level_manager.h"

#include "global_context/kismet_global_context.h"
#include "object/kismet_object_base.h"
#include "object/kismet_object_manager.h"
#include "design_table/kismet_design_table_manager.h"
#include "render/kismet_render_manager.h"
#include "tick/kismet_tick_manager.h"

namespace Kismet
{
	String LevelManager::k_table_name = "level";

	LevelManager::LevelManager()
	{

	}

	LevelManager::~LevelManager()
	{

	}

	void LevelManager::initialize()
	{
		m_generatable_level_unit_array.push_back("Enemy_1");
		m_generatable_level_unit_array.push_back("Enemy_2");
		m_generatable_level_unit_array.push_back("Enemy_3");

		m_generatable_level_unit_array.push_back("Meteorite_1");
		m_generatable_level_unit_array.push_back("Meteorite_2");
		m_generatable_level_unit_array.push_back("Meteorite_3");
		m_generatable_level_unit_array.push_back("Meteorite_4");

		for (size_t index = 0; index < m_generatable_level_unit_array.size(); index++)
		{
			m_generatable_level_unit_map[m_generatable_level_unit_array[index]] = g_global_context.m_design_table_manager->getIntByName(m_generatable_level_unit_array[index], LevelManager::k_table_name, "generate_chance");
		}

		m_generatable_level_unit_array.clear();
	}

	void LevelManager::clear()
	{

	}

	void LevelManager::startLevel()
	{
		if (m_current_level == LevelType::_PREPARE_LEVEL)
		{
			startPrepareLevel();
		}
		else if (m_current_level == LevelType::_GAME_LEVEL)
		{
			startGameLevel();
		}

		m_is_level_started = true;
	}

	void LevelManager::startPrepareLevel()
	{
		g_global_context.m_render_manager->addString("Press \"Space\" to Start Game", 800, 450, 1.f, -1);
		g_global_context.m_render_manager->addString("Press \"H\" to Start Hard Mode", 800, 400, 1.f, -1);

		g_global_context.m_render_manager->addString("\"Enter\" : Upgrade", 800, 300, 1.f, -1);
		g_global_context.m_render_manager->addString("\"Esc\" : End Game", 800, 275, 1.f, -1);
		g_global_context.m_render_manager->addString("\"Backspace\" : Suicide", 800, 250, 1.f, -1);
	}

	void LevelManager::startGameLevel()
	{
		createLevelUnitByName("StarLayer_1");
		createLevelUnitByName("StarLayer_2");
		createLevelUnitByName("MyShip");

		g_global_context.m_render_manager->addString("Lives:", 300, 50, 1.f, -1);
		g_global_context.m_render_manager->addString("HP:", 700, 50, 1.f, -1);
		g_global_context.m_render_manager->addString("Score:", 1100, 50, 1.f, -1);

		g_global_context.m_object_manager->m_live_render_id = g_global_context.m_render_manager->addString("2", 350, 50, 1.f, -1);
		g_global_context.m_object_manager->m_health_render_id = g_global_context.m_render_manager->addString("100", 750, 50, 1.f, -1);
		g_global_context.m_object_manager->m_score_render_id = g_global_context.m_render_manager->addString("0", 1150, 50, 1.f, -1);
	}

	void LevelManager::endLevel()
	{
		g_global_context.clearLevel();
		g_global_context.createLevel();

		if (m_current_level == LevelType::_PREPARE_LEVEL)
		{
			m_current_level = LevelType::_GAME_LEVEL;
		}
		else if (m_current_level == LevelType::_GAME_LEVEL)
		{
			m_current_level = LevelType::_PREPARE_LEVEL;
		}
		m_is_level_started = false;
		
		startLevel();
	}

	void LevelManager::tick()
	{
		if (!m_is_level_started)
		{
			startLevel();
		}

		if (m_current_level == LevelType::_GAME_LEVEL)
		{
			tickGameLevel();
		}
		
	}

	void LevelManager::tickPrepareLevel()
	{
		// TODO
	}

	void LevelManager::tickGameLevel()
	{
		std::map<String, int>::iterator iter;
		for (iter = m_generatable_level_unit_map.begin(); iter != m_generatable_level_unit_map.end(); iter++)
		{
			int random_number = g_global_context.m_random_allocator->generate(10000);
			if (random_number >= 0 && random_number < iter->second)
			{
				createLevelUnitByName(iter->first);			// generate enemy ships and other objects randomly
			}
		}
	}

	int LevelManager::createObjectByName(const String& object_name)
	{
		String type = g_global_context.m_design_table_manager->getStringByName(object_name, ObjectManager::k_table_name, "type");		// hack
		int object_id = 0;
		if (type == "Object")
		{
			object_id = g_global_context.m_object_manager->createObjectByName(object_name);
		}
		else if (type == "Ship")
		{
			object_id = g_global_context.m_object_manager->createShipByName(object_name);
		}
		else if (type == "Bullet")
		{
			object_id = g_global_context.m_object_manager->createBulletByName(object_name);
		}

		return object_id;
	}

	int LevelManager::createObjectByNameAndPosition(const String& object_name, const float position_x, const float position_y)
	{
		int object_id = createObjectByName(object_name);
		if (object_id != NULL)
		{
			ObjectBase* object = g_global_context.m_object_manager->getObjectBaseByID(object_id);
			object->setPosition(position_x, position_y);
		}

		return object_id;
	}

	int LevelManager::createLevelUnitByName(const String& name)
	{
		String object_name = g_global_context.m_design_table_manager->getStringByName(name, LevelManager::k_table_name, "object_name");
		int object_id = createObjectByName(object_name);

		if (object_id != NULL)
		{
			ObjectBase* object = g_global_context.m_object_manager->getObjectBaseByID(object_id);
			float position_x = g_global_context.m_design_table_manager->getFloatByName(name, LevelManager::k_table_name, "position_x");
			float position_y = g_global_context.m_design_table_manager->getFloatByName(name, LevelManager::k_table_name, "position_y");

			float delta_position_y = g_global_context.m_design_table_manager->getFloatByName(name, LevelManager::k_table_name, "delta_position_y");
			if (delta_position_y != 0.f)		// for random generated unit, change its spawning position randomly alse
			{
				int random_number = g_global_context.m_random_allocator->generate(delta_position_y * 2);
				position_y = position_y + random_number - delta_position_y;
			}

			object->setPosition(position_x, position_y);
		}

		return object_id;
	}

	void LevelManager::processInput(Simple2D::KeyCode key_code, ButtonState button_state)
	{
		if (m_current_level == LevelType::_PREPARE_LEVEL)
		{
			processPrepareLevelInput(key_code, button_state);
		}
		else if (m_current_level == LevelType::_GAME_LEVEL)
		{
			processGameLevelInput(key_code, button_state);
		}
		else if (m_current_level == LevelType::_END_LEVEL)
		{
			processEndLevelInput(key_code, button_state);
		}
	}

	void LevelManager::processPrepareLevelInput(Simple2D::KeyCode key_code, ButtonState button_state)
	{
		if (button_state == ButtonState::_PRESSED)
		{
			if (key_code == Simple2D::KEY_SPACE)
			{
				endLevel();
				Root::m_current_difficulity = Difficulity::_NORMAL;
			}
			else if (key_code == Simple2D::KEY_H)
			{
				endLevel();
				Root::m_current_difficulity = Difficulity::_HARD;
			}
		}
		else if (button_state == ButtonState::_PRESSING)
		{

		}
		else if (button_state == ButtonState::_RELEASED)
		{

		}
	}

	void LevelManager::processGameLevelInput(Simple2D::KeyCode key_code, ButtonState button_state)
	{
		if (button_state == ButtonState::_PRESSED)
		{
			if (key_code == Simple2D::KEY_SPACE)
			{
				g_global_context.m_object_manager->processFireAction();
			}
			else if (key_code == Simple2D::KEY_ESCAPE)
			{
				//g_global_context.m_tick_manager->changeGamePauseState();
				endLevel();
				return;
			}
			else if (key_code == Simple2D::KEY_ENTER)
			{
				g_global_context.m_object_manager->processUpgradeAction();
			}
			else if (key_code == Simple2D::KEY_BACKSPACE)
			{
				g_global_context.m_object_manager->processSuicideAction();
			}
			else if (key_code == Simple2D::KEY_UP_ARROW)
			{
				g_global_context.m_object_manager->processYAxisMoveAction(1.f);
			}
			else if (key_code == Simple2D::KEY_DOWN_ARROW)
			{
				g_global_context.m_object_manager->processYAxisMoveAction(-1.f);
			}
			else if (key_code == Simple2D::KEY_LEFT_ARROW)
			{
				g_global_context.m_object_manager->processXAxisMoveAction(-1.f);
			}
			else if (key_code == Simple2D::KEY_RIGHT_ARROW)
			{
				g_global_context.m_object_manager->processXAxisMoveAction(1.f);
			}
		}
		else if (button_state == ButtonState::_PRESSING)
		{
			if (key_code == Simple2D::KEY_UP_ARROW)
			{
				g_global_context.m_object_manager->processYAxisMoveAction(1.f);
			}
			else if (key_code == Simple2D::KEY_DOWN_ARROW)
			{
				g_global_context.m_object_manager->processYAxisMoveAction(-1.f);
			}
			else if (key_code == Simple2D::KEY_LEFT_ARROW)
			{
				g_global_context.m_object_manager->processXAxisMoveAction(-1.f);
			}
			else if (key_code == Simple2D::KEY_RIGHT_ARROW)
			{
				g_global_context.m_object_manager->processXAxisMoveAction(1.f);
			}
		}
		else if (button_state == ButtonState::_RELEASED)
		{
			if (key_code == Simple2D::KEY_UP_ARROW
				|| key_code == Simple2D::KEY_DOWN_ARROW)
			{
				g_global_context.m_object_manager->processCancelYAxisMoveAction();
			}
			else if (key_code == Simple2D::KEY_LEFT_ARROW
				|| key_code == Simple2D::KEY_RIGHT_ARROW)
			{
				g_global_context.m_object_manager->processCancelXAxisMoveAction();
			}
		}
	}

	void LevelManager::processEndLevelInput(Simple2D::KeyCode key_code, ButtonState button_state)
	{
		if (button_state == ButtonState::_PRESSED)
		{

		}
		else if (button_state == ButtonState::_PRESSING)
		{

		}
		else if (button_state == ButtonState::_RELEASED)
		{

		}
	}

}