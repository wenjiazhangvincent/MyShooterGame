#ifndef _KISMET_LEVEL_MANAGER_H_
#define _KISMET_LEVEL_MANAGER_H_
#include "core/kismet_prerequisites.h"

#include "input/kismet_input_manager.h"

namespace Kismet
{
	enum class LevelType :unsigned short
	{
		_PREPARE_LEVEL = 0,
		_GAME_LEVEL = 1,
		_END_LEVEL = 2
	};

	class LevelManager
	{
	public:
		LevelManager();
		~LevelManager();

		static String k_table_name;

		void initialize();
		void clear();

		void startLevel();
		void startPrepareLevel();
		void startGameLevel();
		void endLevel();

		void tick();
		void tickPrepareLevel();
		void tickGameLevel();

		int createObjectByName(const String& object_name);
		int createObjectByNameAndPosition(const String& object_name, const float position_x, const float position_y);
		int createLevelUnitByName(const String& name);

		void processInput(Simple2D::KeyCode key_code, ButtonState button_state);
		void processPrepareLevelInput(Simple2D::KeyCode key_code, ButtonState button_state);
		void processGameLevelInput(Simple2D::KeyCode key_code, ButtonState button_state);
		void processEndLevelInput(Simple2D::KeyCode key_code, ButtonState button_state);
		

	private:
		
		LevelType m_current_level{ LevelType::_PREPARE_LEVEL };

		bool m_is_level_started{ false };


		std::vector<String> m_generatable_level_unit_array;
		std::map<String, int> m_generatable_level_unit_map;
	};

}

#endif // !_KISMET_LEVEL_MANAGER_H_
