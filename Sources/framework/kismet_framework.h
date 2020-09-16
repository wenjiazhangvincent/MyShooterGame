#ifndef _KISMET_FRAMEWORK_H_
#define _KISMET_FRAMEWORK_H_

namespace Kismet
{
	class Framework
	{
	public:
		Framework();
		~Framework();

		void initialize(int argc, char *argv[]);
		bool isInitialized();
		void run();
		void clear();

	private:
		bool m_is_initialized;

	};
}

#endif // !_KISMET_FRAMEWORK_H_
