
#include "../libs/include/irrlicht.h"
#include "../include/System/System.hpp"
#include <csignal>

void signalHandler(int signum)
{
	exit(0);
}
int main()
{
	System sys;
	signal(SIGSEGV, signalHandler);
	signal(SIGABRT, signalHandler);
	sys.start();
	return 0;
}
