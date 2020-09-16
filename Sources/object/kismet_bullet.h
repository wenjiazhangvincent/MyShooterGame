#ifndef _KISMET_BULLET_H_
#define _KISMET_BULLET_H_

#include "object/kismet_object_base.h"

namespace Kismet
{
	class Bullet:public ObjectBase
	{
	public:
		Bullet() {};
		~Bullet() {};
		Bullet(const String& bullet_name);


	private:
		int mm{0};
	};
}

#endif // !_KISMET_BULLET_H_
