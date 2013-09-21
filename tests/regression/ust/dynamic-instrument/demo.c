#include <unistd.h>

void foo() {
    usleep(1);
}

int main()
{
    int i;
    for (i = 0; i < 10; ++i)
        foo();
    return 0;
}
