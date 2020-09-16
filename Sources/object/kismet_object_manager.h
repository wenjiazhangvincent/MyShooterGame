#ifndef _KISMET_object_MANAGER_H_
#define _KISMET_object_MANAGER_H_
#include "core/kismet_prerequisites.h"
#include "object/kismet_object_base.h"
#include "object/kismet_object.h"
#include "object/kismet_ship.h"
#include "object/kismet_bullet.h"

namespace Kismet
{
	class ObjectManager
	{
	public:
		ObjectManager();
		~ObjectManager();

		//static Vector2<float> k_background_speed;
		static String k_table_name;

		void initialize();
		void clear();
		void tick();
		void postTick();

		ObjectBase* getObjectBaseByID(int object_id);
		void deleteObjectBaseByID(int object_id);

		bool hasObjectID(int object_id);
		Object* getObjectByID(int object_id);
		int createObjectByName(const String& object_name);

		bool hasShipID(int object_id);
		Ship* getShipByID(int object_id);
		int createShipByName(const String& ship_name);

		bool hasBulletID(int object_id);
		Bullet* getBulletByID(int object_id);
		int createBulletByName(const String& bullet_name);
		
		void processUpgradeAction();		// for cheating and debugging, which shouldn't exist in this manager
		void processSuicideAction();		// for cheating and debugging, which shouldn't exist in this manager
		void processFireAction();
		void processXAxisMoveAction(float x);
		void processYAxisMoveAction(float y);
		void processCancelXAxisMoveAction();
		void processCancelYAxisMoveAction();

		int m_my_ship_object_id;

		int m_my_ship_live_remains;
		int m_my_ship_current_health;
		int m_my_ship_score;
		int m_live_render_id;
		int m_health_render_id;
		int m_score_render_id;

		static float k_my_ship_speed_times;		// my ship move pixes for each frame

	private:


		IDAllocator<ObjectBase> m_object_id_allocator;

		std::map<int, Object> m_object_map;
		std::map<int, Ship> m_ship_map;
		std::map<int, Bullet> m_bullet_map;

		std::vector<int> m_delete_object_id_array;
	};

}

#endif // !_KISMET_object_MANAGER_H_
