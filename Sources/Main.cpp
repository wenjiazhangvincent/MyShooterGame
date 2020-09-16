#include "framework/kismet_framework.h"
#include <iostream>

int main(int argc, char *argv[])
{
	Kismet::Framework framework;
	framework.initialize(argc, argv);

	if (framework.isInitialized())
	{
		framework.run();
	}


	framework.clear();
}
