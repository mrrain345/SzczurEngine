#include <SzczurEngine/Game.h>

#ifdef __unix__
	#include <execinfo.h>
	#include <signal.h>
	#include <unistd.h>
	#include <iostream>

	void backtrace(int sig) {
		void *array[512];
		size_t size = backtrace(array, 512);

		std::cerr << "Error: Segmentation fault" << std::endl;
		backtrace_symbols_fd(array, size, STDERR_FILENO);
		exit(1);
	}
#endif

int main() {
#ifdef __unix__
	signal(SIGSEGV, backtrace);
#endif

#ifdef SZCZUR_EDITOR
	Szczur::Game::init("SzczurEngine v0.00000001-pre-pre-alpha", 1370, 688);
#else
	Szczur::Game::init("SzczurEngine v0.00000001-pre-pre-alpha", 1120, 640);
#endif
	return 0;
}
