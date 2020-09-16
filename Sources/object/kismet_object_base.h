#ifndef _KISMET_OBJECT_BASE_H_
#define _KISMET_OBJECT_BASE_H_
#include "core/kismet_prerequisites.h"
#include "root/kimset_root.h"

namespace Kismet
{
	enum class TeamID :unsigned int
	{
		_TEAM_NEUTRAL = 0,
		_TEAM_SELF = 1,
		_TEAM_HOSTILE = 2,
		_TEAM_INVULNERABLE = 3,
		_COUNT
	};

	class ObjectBase
	{
	public:
		ObjectBase() {};
		~ObjectBase() {};
		ObjectBase(const String& object_name);

		void setObjectID(int object_id);

		Simple2D::Image* getImage();

		void setSpeed(float x, float y);
		void move();

		bool isInMainWindow();

		void setPosition(float position_x, float position_y);
		Vector2<float>* getPosition();
		float getRotation();
		float getScale();

		void setTeamID(int int_team_id);
		TeamID getTeamID();
		bool isNeutral();
		bool isSelf();
		bool isHostile();

		void setDamage(const int damage);
		unsigned int getDamege();

		bool isInLoop();
		void changePositionForLoop();

		int m_object_id{ -1 };
		String m_object_name{ "" };
		Simple2D::Image* m_image{ nullptr };

		Vector2<int> m_size{ 0,0 };
		Vector2<float> m_position{ 0.f, 0.f };
		Vector2<float> m_speed{ 0.f, 0.f };
		float m_rotation{ 0.f };
		float m_scale{ 1.f };

		TeamID m_team_id{ TeamID(0) };
		bool m_is_deleted_after_colliding{ false };
		long m_duration{ -1 };
		unsigned int m_damage{ 0 };
		bool m_is_in_loop{ false };			/* in order to make the background moving constantly, I choose to render 2 background image loop by loop
												which doesn't look pretty (maybe some computer graphic ways can combine 2 images perfectly)		*/
	};

}

#endif // !_KISMET_OBJECT_BASE_H_
