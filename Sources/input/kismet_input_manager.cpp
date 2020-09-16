#include "input/kismet_input_manager.h"

#include "global_context/kismet_global_context.h"
#include "level/kismet_level_manager.h"
#include "tick/kismet_tick_manager.h"
#include "root/kimset_root.h"

namespace Kismet
{
	//Simple2D::KeyCode InputManager::k_game_pause_key = Simple2D::KEY_ESCAPE;

	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::initialize()
	{
		m_pressed_key_check_array.push_back(Simple2D::KEY_SPACE);
		m_pressed_key_check_array.push_back(Simple2D::KEY_ESCAPE);
		m_pressed_key_check_array.push_back(Simple2D::KEY_ENTER);
		m_pressed_key_check_array.push_back(Simple2D::KEY_BACKSPACE);
		m_pressed_key_check_array.push_back(Simple2D::KEY_UP_ARROW);
		m_pressed_key_check_array.push_back(Simple2D::KEY_DOWN_ARROW);
		m_pressed_key_check_array.push_back(Simple2D::KEY_LEFT_ARROW);
		m_pressed_key_check_array.push_back(Simple2D::KEY_RIGHT_ARROW);
		m_pressed_key_check_array.push_back(Simple2D::KEY_H);

		m_pressing_key_check_array.push_back(Simple2D::KEY_UP_ARROW);
		m_pressing_key_check_array.push_back(Simple2D::KEY_DOWN_ARROW);
		m_pressing_key_check_array.push_back(Simple2D::KEY_LEFT_ARROW);
		m_pressing_key_check_array.push_back(Simple2D::KEY_RIGHT_ARROW);

		m_released_key_check_array.push_back(Simple2D::KEY_UP_ARROW);
		m_released_key_check_array.push_back(Simple2D::KEY_DOWN_ARROW);
		m_released_key_check_array.push_back(Simple2D::KEY_LEFT_ARROW);
		m_released_key_check_array.push_back(Simple2D::KEY_RIGHT_ARROW);

		registerToCheckMap(&m_pressed_key_check_array);
		registerToCheckMap(&m_pressing_key_check_array);
		registerToCheckMap(&m_released_key_check_array);
	}

	void InputManager::clear()
	{

	}

	void InputManager::registerToCheckMap(std::vector<Simple2D::KeyCode>* check_array)
	{
		for (size_t index = 0; index < (*check_array).size(); index++)
		{
			std::map<Simple2D::KeyCode, ButtonStates>::iterator iter = m_key_check_map.find((*check_array)[index]);
			if (iter == m_key_check_map.end())
			{
				m_key_check_map[(*check_array)[index]] = ButtonStates();
			}
		}
	}

	void InputManager::tick()
	{
		if (Root::m_current_difficulity == Difficulity::_NORMAL)
		{
			tickButtonStates();
		}
		else if(Root::m_current_difficulity == Difficulity::_HARD)
		{
			tickButtonStatesWithInertia();
		}
		tickInputDemands();
	}

	void InputManager::tickButtonStates()
	{
		std::map<Simple2D::KeyCode, ButtonStates>::iterator iter;
		for (iter = m_key_check_map.begin(); iter != m_key_check_map.end(); iter++)
		{
			/*if (g_global_context.m_tick_manager->isGamePaused() && iter->first != k_game_pause_key)
			{
				continue;
			}*/

			ButtonStates* states = &iter->second;
			if (Simple2D::IsKeyPressed(iter->first))
			{
				states->m_previous_state = states->m_current_state;
				states->m_current_state = ButtonState::_PRESSED;
			}
			else if (Simple2D::IsKeyReleased(iter->first))
			{
				states->m_previous_state = states->m_current_state;
				states->m_current_state = ButtonState::_RELEASED;
			}
			else
			{
				if (states->m_current_state == ButtonState::_PRESSED
					|| states->m_current_state == ButtonState::_PRESSING)
				{
					states->m_previous_state = states->m_current_state;
					states->m_current_state = ButtonState::_PRESSING;
				}
				else
				{
					states->m_previous_state = states->m_current_state;
					states->m_current_state = ButtonState::_NONE;
				}
			}
		}
	}

	void InputManager::tickButtonStatesWithInertia()
	{
		std::map<Simple2D::KeyCode, ButtonStates>::iterator iter;
		for (iter = m_key_check_map.begin(); iter != m_key_check_map.end(); iter++)
		{
			/*if (g_global_context.m_tick_manager->isGamePaused() && iter->first != k_game_pause_key)
			{
				continue;
			}*/

			ButtonStates* states = &iter->second;
			if (Simple2D::IsKeyPressed(iter->first))
			{
				states->m_previous_state = states->m_current_state;
				states->m_current_state = ButtonState::_PRESSED;
			}
			else if (Simple2D::IsKeyReleased(iter->first))
			{
				ButtonState temp_previous_state;
				temp_previous_state = states->m_previous_state;
				states->m_previous_state = states->m_current_state;

				if (temp_previous_state == ButtonState::_PRESSED
					|| temp_previous_state == ButtonState::_PRESSING)
				{
					states->m_current_state = ButtonState::_PRESSING;
				}
				else if (temp_previous_state == ButtonState::_RELEASED)
				{
					states->m_current_state = ButtonState::_RELEASED;
				}
				else
				{
					states->m_current_state = ButtonState::_NONE;
				}
			}
		}
	}

	void InputManager::tickInputDemands()
	{
		checkInputDemandsByButtonState(&m_pressed_key_check_array, ButtonState::_PRESSED);
		checkInputDemandsByButtonState(&m_pressing_key_check_array, ButtonState::_PRESSING);
		checkInputDemandsByButtonState(&m_released_key_check_array, ButtonState::_RELEASED);
	}


	void InputManager::checkInputDemandsByButtonState(std::vector<Simple2D::KeyCode>* check_array, ButtonState check_button_state)
	{
		ButtonState current_button_state;
		for (size_t index = 0; index < (*check_array).size(); index++)
		{
			current_button_state = getKeyButtonState((*check_array)[index]);
			if (current_button_state == check_button_state)
			{
				g_global_context.m_level_manager->processInput((*check_array)[index], current_button_state);
			}
		}
	}

	ButtonState InputManager::getKeyButtonState(Simple2D::KeyCode key_code)
	{
		std::map<Simple2D::KeyCode, ButtonStates>::iterator iter = m_key_check_map.find(key_code);
		if (iter != m_key_check_map.end())
		{
			return iter->second.m_current_state;
		}

		return ButtonState::_RELEASED;
	}

}