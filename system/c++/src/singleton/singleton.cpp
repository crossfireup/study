#include "singleton.h"

int main(void)
{
    Singleton::getInstance().log("singleton log");

    return 0;
}
