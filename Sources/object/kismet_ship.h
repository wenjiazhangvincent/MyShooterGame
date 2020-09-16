#ifndef _KISMET_SHIP_H_
#define _KISMET_SHIP_H_

#include "object/kismet_object_base.h"
#include "object/kismet_bullet.h"

namespace Kismet
{
	class Ship:public ObjectBase
	{
	public:
		Ship() {};
		~Ship() {};
		Ship(const String& ship_name);

		void fire(bool is_my_ship);
		void tryFire();

		void beHit(bool is_my_ship);
		void die(bool is_my_ship);

		bool isUpgradable();
		void upgrade();
		void tryUpgrade();

		void changePositionRelatively(float x, float y);
		void changeXAxisSpeed(float x);
		void changeYAxisSpeed(float y);

		void setHealth(const int health);
		void changeHealth(const int delta_health);
		void restoreFullHealth();
		int getHealth();

	private:
		String m_bullet_name{ "" };
		int m_fire_chance{ 0 };		// per ten thousand  
		int m_health{ 100 };
		int m_experience{ 0 };
		int m_level_up_exp{ 0 };
		String m_next_level_name{ "" };
	};

}

#endif // !_KISMET_SHIP_H_
