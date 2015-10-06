#include "base/test/ConfigTest.h"
#include "base/test/LoggerTest.h"
#include "base/test/LinAlgTest.h"

int main()
{
    base_test::logger_test();
    base_test::config_test();
    base_test::lin_alg_test();

    return 0;
}
