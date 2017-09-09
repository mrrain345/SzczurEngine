#include <Szczur/System/Game.h>

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
	Szczur::Game::Init("Projekt M.Y.S.Z v0.000000000001-pre-pre-alpha", 1120, 640);
	return 0;
}
