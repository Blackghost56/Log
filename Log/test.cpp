#include "test.h"

Test::Test()
{
    LogCore& instance = LogCore::getInstance();

    instance.add("Test");
}
