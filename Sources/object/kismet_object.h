#ifndef _KISMET_OBJECT_H_
#define _KISMET_OBJECT_H_

#include "object/kismet_object.h"

namespace Kismet
{
	class Object :public ObjectBase
	{
	public:
		Object() {};
		~Object() {}
		Object(const String& object_name);
	};

}

#endif // !_KISMET_OBJECT_H_
