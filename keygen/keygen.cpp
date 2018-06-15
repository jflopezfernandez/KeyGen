// keygen.cpp : Defines the entry point for the application.
//

//#include "keygen.h"

#include <cstdlib>
#include <iostream>

/**#include <boost/program_options.hpp>*/

// TODO: Incorporate glog
/**#include <glog/config.h>
#include <glog/stl_logging.h>
#include <glog/logging.h>

#include <gtest/gtest.h>*/

/**int returnOne() {
    return 1;
}

TEST(GTestConfig, TrivialTest)
{
    EXPECT_EQ(1, returnOne());
}*/


int main(int argc, char *argv[])
{
    if (argc == 1) {
        std::cout << "Usage: keygen <opts>\n";

        return EXIT_FAILURE;
    }

    for (auto i = 1u; i < argc; i++) {
        std::cout << argv[i] << '\n';
    }

    return EXIT_SUCCESS;

    /**testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();*/
}
