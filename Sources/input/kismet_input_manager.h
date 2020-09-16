#ifndef _KISMET_INPUT_MANAGER_H_
#define _KISMET_INPUT_MANAGER_H_
#include "core/kismet_prerequisites.h"

namespace Kismet
{
	enum class ButtonState :unsigned char
	{
		_NONE,
		_PRESSED,
		_PRESSING,
		_RELEASED,
	};

	class ButtonStates
	{
	public:
		ButtonStates()
		{
			m_previous_state = ButtonState::_NONE;
			m_current_state = ButtonState::_NONE;
		}

		ButtonState m_previous_state;
		ButtonState m_current_state;
	};

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void initialize();
		void clear();

		void registerToCheckMap(std::vector<Simple2D::KeyCode>* check_array);

		void tick();
		void tickButtonStates();		// check button state
		void tickButtonStatesWithInertia();		// check button state with inertia
		void tickInputDemands();		// check input demands
		void checkInputDemandsByButtonState(std::vector<Simple2D::KeyCode>* check_array, ButtonState check_button_state);

		ButtonState getKeyButtonState(Simple2D::KeyCode key_code);

		//static Simple2D::KeyCode k_game_pause_key;

	private:

		std::map<Simple2D::KeyCode, ButtonStates> m_key_check_map;

		std::vector<Simple2D::KeyCode> m_pressed_key_check_array;
		std::vector<Simple2D::KeyCode> m_pressing_key_check_array;
		std::vector<Simple2D::KeyCode> m_released_key_check_array;
	};
}

#endif // !_KISMET_INPUT_MANAGER_H_
