#include <unistd.h>

void foo(void) {
	usleep(1);
}

int main()
{
	int i;
	/* Do not let gcc optimize foo out */
	void (*call_foo)(void) = foo;

	for (i = 0; i < 10; i++)
		call_foo();
	return 0;
}
