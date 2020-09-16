#ifndef _KISMET_TYPES_H_
#define _KISMET_TYPES_H_

#include <string>

namespace Kismet
{
	// Vector2
	template <class T>
	struct Vector2
	{
		T m_x;
		T m_y;

		Vector2() {};
		Vector2(T x, T y) { m_x = x; m_y = y; };

		Vector2& operator +=(const Vector2<T>& A)
		{
			m_x = m_x + A.m_x;
			m_y = m_y + A.m_y;
			return *this;
		}

		Vector2& operator -=(const Vector2<T>& A)
		{
			m_x = m_x - A.m_x;
			m_y = m_y - A.m_y;
			return *this;
		}
	};


	using String = std::string;

}

#endif // !_KISMET_TYPES_H_
