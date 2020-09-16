#include "framework/kismet_framework.h"
#include "root/kimset_root.h"

namespace Kismet
{
	Framework::Framework()
	{
		m_is_initialized = false;
		Root::startGame();
	}

	Framework::~Framework()
	{
		Root::shutDownGame();
	}

	void Framework::initialize(int argc, char *argv[])
	{
		Root::initialize(argc, argv);
		m_is_initialized = true;
	}

	bool Framework::isInitialized()
	{
		return m_is_initialized;
	}

	void Framework::run()
	{
		Root::run();
	}

	void Framework::clear()
	{
		Root::clear();
		m_is_initialized = false;
	}
}